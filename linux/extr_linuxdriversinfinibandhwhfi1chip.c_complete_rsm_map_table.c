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
struct rsm_map_table {int /*<<< orphan*/ * map; } ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int NUM_MAP_REGS ; 
 int /*<<< orphan*/  RCV_CTRL_RCV_RSM_ENABLE_SMASK ; 
 scalar_t__ RCV_RSM_MAP_TABLE ; 
 int /*<<< orphan*/  add_rcvctrl (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void complete_rsm_map_table(struct hfi1_devdata *dd,
				   struct rsm_map_table *rmt)
{
	int i;

	if (rmt) {
		/* write table to chip */
		for (i = 0; i < NUM_MAP_REGS; i++)
			write_csr(dd, RCV_RSM_MAP_TABLE + (8 * i), rmt->map[i]);

		/* enable RSM */
		add_rcvctrl(dd, RCV_CTRL_RCV_RSM_ENABLE_SMASK);
	}
}