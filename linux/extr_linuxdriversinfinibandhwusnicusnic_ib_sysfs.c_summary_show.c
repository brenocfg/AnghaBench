#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usnic_vnic_res_chunk {int cnt; struct usnic_vnic_res** res; } ;
struct usnic_vnic_res {int /*<<< orphan*/  vnic_idx; int /*<<< orphan*/  type; } ;
struct TYPE_3__ {int /*<<< orphan*/  qp_num; } ;
struct usnic_ib_qp_grp {struct usnic_vnic_res_chunk** res_chunk_list; TYPE_2__* vf; int /*<<< orphan*/  owner_pid; int /*<<< orphan*/  state; TYPE_1__ ibqp; } ;
typedef  int ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  vnic; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  UPDATE_PTR_LEFT (int,char*,int) ; 
 int scnprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  usnic_ib_qp_grp_state_to_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usnic_vnic_get_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usnic_vnic_res_type_to_str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t summary_show(struct usnic_ib_qp_grp *qp_grp, char *buf)
{
	int i, j, n;
	int left;
	char *ptr;
	struct usnic_vnic_res_chunk *res_chunk;
	struct usnic_vnic_res *vnic_res;

	left = PAGE_SIZE;
	ptr = buf;

	n = scnprintf(ptr, left,
			"QPN: %d State: (%s) PID: %u VF Idx: %hu ",
			qp_grp->ibqp.qp_num,
			usnic_ib_qp_grp_state_to_string(qp_grp->state),
			qp_grp->owner_pid,
			usnic_vnic_get_index(qp_grp->vf->vnic));
	UPDATE_PTR_LEFT(n, ptr, left);

	for (i = 0; qp_grp->res_chunk_list[i]; i++) {
		res_chunk = qp_grp->res_chunk_list[i];
		for (j = 0; j < res_chunk->cnt; j++) {
			vnic_res = res_chunk->res[j];
			n = scnprintf(ptr, left, "%s[%d] ",
				usnic_vnic_res_type_to_str(vnic_res->type),
				vnic_res->vnic_idx);
			UPDATE_PTR_LEFT(n, ptr, left);
		}
	}

	n = scnprintf(ptr, left, "\n");
	UPDATE_PTR_LEFT(n, ptr, left);

	return ptr - buf;
}