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
typedef  int /*<<< orphan*/  u32 ;
struct fusb300_ep_info {int maxpacket; int /*<<< orphan*/  epnum; } ;
struct fusb300 {int addrofs; scalar_t__ reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUSB300_EPSET2_ADDROFS (int) ; 
 int /*<<< orphan*/  FUSB300_EPSET2_ADDROFS_MSK ; 
 int FUSB300_FIFO_ENTRY_NUM ; 
 scalar_t__ FUSB300_OFFSET_EPSET2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void fusb300_set_epaddrofs(struct fusb300 *fusb300,
				  struct fusb300_ep_info info)
{
	u32 reg = ioread32(fusb300->reg + FUSB300_OFFSET_EPSET2(info.epnum));

	reg &= ~FUSB300_EPSET2_ADDROFS_MSK;
	reg |= FUSB300_EPSET2_ADDROFS(fusb300->addrofs);
	iowrite32(reg, fusb300->reg + FUSB300_OFFSET_EPSET2(info.epnum));
	fusb300->addrofs += (info.maxpacket + 7) / 8 * FUSB300_FIFO_ENTRY_NUM;
}