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
struct netup_unidvb_dev {scalar_t__ bmmio0; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ CAM_CTRLSTAT_CLR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

irqreturn_t netup_ci_interrupt(struct netup_unidvb_dev *ndev)
{
	writew(0x101, ndev->bmmio0 + CAM_CTRLSTAT_CLR);
	return IRQ_HANDLED;
}