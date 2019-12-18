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
struct qib_pportdata {int /*<<< orphan*/  hw_pidx; int /*<<< orphan*/  dd; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBSD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahb_mod (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 

__attribute__((used)) static void set_man_mode_h1(struct qib_pportdata *ppd, int chan,
	int enable, u32 tapenable)
{
	if (enable)
		ahb_mod(ppd->dd, IBSD(ppd->hw_pidx), (chan + (chan >> 1)),
			1, 3 << 10, 0x1f << 10);
	else
		ahb_mod(ppd->dd, IBSD(ppd->hw_pidx), (chan + (chan >> 1)),
			1, 0, 0x1f << 10);
}