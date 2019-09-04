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
struct sti_vid {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ VID_CTL ; 
 int /*<<< orphan*/  VID_CTL_IGNORE ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

void sti_vid_disable(struct sti_vid *vid)
{
	u32 val;

	/* Mask */
	val = readl(vid->regs + VID_CTL);
	val |= VID_CTL_IGNORE;
	writel(val, vid->regs + VID_CTL);
}