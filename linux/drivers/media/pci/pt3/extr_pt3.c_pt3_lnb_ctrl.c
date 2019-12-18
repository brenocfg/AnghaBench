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
struct pt3_board {scalar_t__* regs; } ;

/* Variables and functions */
 scalar_t__ REG_SYSTEM_W ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 

__attribute__((used)) static inline void pt3_lnb_ctrl(struct pt3_board *pt3, bool on)
{
	iowrite32((on ? 0x0f : 0x0c), pt3->regs[0] + REG_SYSTEM_W);
}