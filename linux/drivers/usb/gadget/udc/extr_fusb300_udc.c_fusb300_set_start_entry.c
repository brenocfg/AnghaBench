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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct fusb300 {int fifo_entry_num; scalar_t__ addrofs; scalar_t__ reg; } ;

/* Variables and functions */
 int FUSB300_EPSET1_START_ENTRY (int) ; 
 int FUSB300_EPSET1_START_ENTRY_MSK ; 
 int FUSB300_FIFO_ENTRY_NUM ; 
 int FUSB300_MAX_FIFO_ENTRY ; 
 scalar_t__ FUSB300_OFFSET_EPSET1 (int /*<<< orphan*/ ) ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static void fusb300_set_start_entry(struct fusb300 *fusb300,
				    u8 ep)
{
	u32 reg = ioread32(fusb300->reg + FUSB300_OFFSET_EPSET1(ep));
	u32 start_entry = fusb300->fifo_entry_num * FUSB300_FIFO_ENTRY_NUM;

	reg &= ~FUSB300_EPSET1_START_ENTRY_MSK	;
	reg |= FUSB300_EPSET1_START_ENTRY(start_entry);
	iowrite32(reg, fusb300->reg + FUSB300_OFFSET_EPSET1(ep));
	if (fusb300->fifo_entry_num == FUSB300_MAX_FIFO_ENTRY) {
		fusb300->fifo_entry_num = 0;
		fusb300->addrofs = 0;
		pr_err("fifo entry is over the maximum number!\n");
	} else
		fusb300->fifo_entry_num++;
}