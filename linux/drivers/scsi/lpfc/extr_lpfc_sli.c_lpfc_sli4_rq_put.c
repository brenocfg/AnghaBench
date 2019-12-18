#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct lpfc_rqe {int dummy; } ;
struct lpfc_register {scalar_t__ word0; } ;
struct lpfc_queue {int host_index; scalar_t__ type; int entry_count; int hba_index; int notify_interval; scalar_t__ db_format; int queue_id; int /*<<< orphan*/  db_regaddr; int /*<<< orphan*/  RQ_buf_posted; int /*<<< orphan*/  entry_size; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ LPFC_DB_LIST_FORMAT ; 
 scalar_t__ LPFC_DB_RING_FORMAT ; 
 scalar_t__ LPFC_DRQ ; 
 scalar_t__ LPFC_HRQ ; 
 int /*<<< orphan*/  bf_set (int /*<<< orphan*/ ,struct lpfc_register*,int) ; 
 int /*<<< orphan*/  lpfc_rq_db_list_fm_id ; 
 int /*<<< orphan*/  lpfc_rq_db_list_fm_index ; 
 int /*<<< orphan*/  lpfc_rq_db_list_fm_num_posted ; 
 int /*<<< orphan*/  lpfc_rq_db_ring_fm_id ; 
 int /*<<< orphan*/  lpfc_rq_db_ring_fm_num_posted ; 
 int /*<<< orphan*/  lpfc_sli4_pcimem_bcopy (struct lpfc_rqe*,struct lpfc_rqe*,int /*<<< orphan*/ ) ; 
 struct lpfc_rqe* lpfc_sli4_qe (struct lpfc_queue*,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  writel (scalar_t__,int /*<<< orphan*/ ) ; 

int
lpfc_sli4_rq_put(struct lpfc_queue *hq, struct lpfc_queue *dq,
		 struct lpfc_rqe *hrqe, struct lpfc_rqe *drqe)
{
	struct lpfc_rqe *temp_hrqe;
	struct lpfc_rqe *temp_drqe;
	struct lpfc_register doorbell;
	int hq_put_index;
	int dq_put_index;

	/* sanity check on queue memory */
	if (unlikely(!hq) || unlikely(!dq))
		return -ENOMEM;
	hq_put_index = hq->host_index;
	dq_put_index = dq->host_index;
	temp_hrqe = lpfc_sli4_qe(hq, hq_put_index);
	temp_drqe = lpfc_sli4_qe(dq, dq_put_index);

	if (hq->type != LPFC_HRQ || dq->type != LPFC_DRQ)
		return -EINVAL;
	if (hq_put_index != dq_put_index)
		return -EINVAL;
	/* If the host has not yet processed the next entry then we are done */
	if (((hq_put_index + 1) % hq->entry_count) == hq->hba_index)
		return -EBUSY;
	lpfc_sli4_pcimem_bcopy(hrqe, temp_hrqe, hq->entry_size);
	lpfc_sli4_pcimem_bcopy(drqe, temp_drqe, dq->entry_size);

	/* Update the host index to point to the next slot */
	hq->host_index = ((hq_put_index + 1) % hq->entry_count);
	dq->host_index = ((dq_put_index + 1) % dq->entry_count);
	hq->RQ_buf_posted++;

	/* Ring The Header Receive Queue Doorbell */
	if (!(hq->host_index % hq->notify_interval)) {
		doorbell.word0 = 0;
		if (hq->db_format == LPFC_DB_RING_FORMAT) {
			bf_set(lpfc_rq_db_ring_fm_num_posted, &doorbell,
			       hq->notify_interval);
			bf_set(lpfc_rq_db_ring_fm_id, &doorbell, hq->queue_id);
		} else if (hq->db_format == LPFC_DB_LIST_FORMAT) {
			bf_set(lpfc_rq_db_list_fm_num_posted, &doorbell,
			       hq->notify_interval);
			bf_set(lpfc_rq_db_list_fm_index, &doorbell,
			       hq->host_index);
			bf_set(lpfc_rq_db_list_fm_id, &doorbell, hq->queue_id);
		} else {
			return -EINVAL;
		}
		writel(doorbell.word0, hq->db_regaddr);
	}
	return hq_put_index;
}