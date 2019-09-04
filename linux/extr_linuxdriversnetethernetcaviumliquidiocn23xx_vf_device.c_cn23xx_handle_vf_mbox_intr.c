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
typedef  int /*<<< orphan*/  u64 ;
struct octeon_ioq_vector {int /*<<< orphan*/  droq_index; struct octeon_device* oct_dev; } ;
struct octeon_device {TYPE_2__** mbox; } ;
struct TYPE_3__ {int /*<<< orphan*/  work; } ;
struct TYPE_4__ {TYPE_1__ mbox_poll_wk; int /*<<< orphan*/  mbox_int_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ octeon_mbox_read (TYPE_2__*) ; 
 int /*<<< orphan*/  readq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cn23xx_handle_vf_mbox_intr(struct octeon_ioq_vector *ioq_vector)
{
	struct octeon_device *oct = ioq_vector->oct_dev;
	u64 mbox_int_val;

	if (!ioq_vector->droq_index) {
		/* read and clear by writing 1 */
		mbox_int_val = readq(oct->mbox[0]->mbox_int_reg);
		writeq(mbox_int_val, oct->mbox[0]->mbox_int_reg);
		if (octeon_mbox_read(oct->mbox[0]))
			schedule_delayed_work(&oct->mbox[0]->mbox_poll_wk.work,
					      msecs_to_jiffies(0));
	}
}