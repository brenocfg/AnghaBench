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
typedef  int u64 ;
struct hfi1_pportdata {int* pkeys; struct hfi1_devdata* dd; } ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCV_CTRL_RCV_PARTITION_KEY_ENABLE_SMASK ; 
 scalar_t__ RCV_PARTITION_KEY ; 
 int RCV_PARTITION_KEY_PARTITION_KEY_A_MASK ; 
 int RCV_PARTITION_KEY_PARTITION_KEY_B_SHIFT ; 
 int /*<<< orphan*/  add_rcvctrl (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dd_dev_info (struct hfi1_devdata*,char*) ; 
 int hfi1_get_npkeys (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,scalar_t__,int) ; 

__attribute__((used)) static void set_partition_keys(struct hfi1_pportdata *ppd)
{
	struct hfi1_devdata *dd = ppd->dd;
	u64 reg = 0;
	int i;

	dd_dev_info(dd, "Setting partition keys\n");
	for (i = 0; i < hfi1_get_npkeys(dd); i++) {
		reg |= (ppd->pkeys[i] &
			RCV_PARTITION_KEY_PARTITION_KEY_A_MASK) <<
			((i % 4) *
			 RCV_PARTITION_KEY_PARTITION_KEY_B_SHIFT);
		/* Each register holds 4 PKey values. */
		if ((i % 4) == 3) {
			write_csr(dd, RCV_PARTITION_KEY +
				  ((i - 3) * 2), reg);
			reg = 0;
		}
	}

	/* Always enable HW pkeys check when pkeys table is set */
	add_rcvctrl(dd, RCV_CTRL_RCV_PARTITION_KEY_ENABLE_SMASK);
}