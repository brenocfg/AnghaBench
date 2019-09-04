#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  size_t u32 ;
struct TYPE_4__ {size_t num_vfs_alloced; size_t rings_per_vf; } ;
struct octeon_device {TYPE_3__** mbox; TYPE_1__ sriov_info; } ;
struct delayed_work {int dummy; } ;
struct TYPE_5__ {struct delayed_work work; } ;
struct TYPE_6__ {TYPE_2__ mbox_poll_wk; int /*<<< orphan*/  mbox_int_reg; } ;

/* Variables and functions */
 int BIT_ULL (size_t) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ octeon_mbox_read (TYPE_3__*) ; 
 int readq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (struct delayed_work*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeq (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cn23xx_handle_pf_mbox_intr(struct octeon_device *oct)
{
	struct delayed_work *work;
	u64 mbox_int_val;
	u32 i, q_no;

	mbox_int_val = readq(oct->mbox[0]->mbox_int_reg);

	for (i = 0; i < oct->sriov_info.num_vfs_alloced; i++) {
		q_no = i * oct->sriov_info.rings_per_vf;

		if (mbox_int_val & BIT_ULL(q_no)) {
			writeq(BIT_ULL(q_no),
			       oct->mbox[0]->mbox_int_reg);
			if (octeon_mbox_read(oct->mbox[q_no])) {
				work = &oct->mbox[q_no]->mbox_poll_wk.work;
				schedule_delayed_work(work,
						      msecs_to_jiffies(0));
			}
		}
	}
}