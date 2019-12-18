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
typedef  int /*<<< orphan*/  u32 ;
struct iser_fr_desc {int dummy; } ;
struct iser_conn {int /*<<< orphan*/  iscsi_conn; int /*<<< orphan*/  snd_w_inv; } ;
struct iscsi_task {struct iscsi_iser_task* dd_data; } ;
struct iscsi_iser_task {TYPE_2__* rdma_reg; scalar_t__* dir; } ;
struct iscsi_hdr {struct iser_conn* itt; } ;
struct TYPE_3__ {int /*<<< orphan*/  invalidate_rkey; } ;
struct ib_wc {int wc_flags; TYPE_1__ ex; } ;
struct TYPE_4__ {struct iser_fr_desc* mem_h; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPROTO ; 
 int IB_WC_WITH_INVALIDATE ; 
 size_t ISER_DIR_IN ; 
 size_t ISER_DIR_OUT ; 
 struct iscsi_task* iscsi_itt_to_ctask (int /*<<< orphan*/ ,struct iser_conn*) ; 
 int /*<<< orphan*/  iser_dbg (char*,struct iser_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iser_err (char*,struct iser_conn*) ; 
 int iser_inv_desc (struct iser_fr_desc*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (struct iscsi_task*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
iser_check_remote_inv(struct iser_conn *iser_conn,
		      struct ib_wc *wc,
		      struct iscsi_hdr *hdr)
{
	if (wc->wc_flags & IB_WC_WITH_INVALIDATE) {
		struct iscsi_task *task;
		u32 rkey = wc->ex.invalidate_rkey;

		iser_dbg("conn %p: remote invalidation for rkey %#x\n",
			 iser_conn, rkey);

		if (unlikely(!iser_conn->snd_w_inv)) {
			iser_err("conn %p: unexpected remote invalidation, terminating connection\n",
				 iser_conn);
			return -EPROTO;
		}

		task = iscsi_itt_to_ctask(iser_conn->iscsi_conn, hdr->itt);
		if (likely(task)) {
			struct iscsi_iser_task *iser_task = task->dd_data;
			struct iser_fr_desc *desc;

			if (iser_task->dir[ISER_DIR_IN]) {
				desc = iser_task->rdma_reg[ISER_DIR_IN].mem_h;
				if (unlikely(iser_inv_desc(desc, rkey)))
					return -EINVAL;
			}

			if (iser_task->dir[ISER_DIR_OUT]) {
				desc = iser_task->rdma_reg[ISER_DIR_OUT].mem_h;
				if (unlikely(iser_inv_desc(desc, rkey)))
					return -EINVAL;
			}
		} else {
			iser_err("failed to get task for itt=%d\n", hdr->itt);
			return -EINVAL;
		}
	}

	return 0;
}