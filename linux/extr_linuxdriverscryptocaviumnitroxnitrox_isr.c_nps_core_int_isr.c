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
struct nitrox_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  clear_nps_core_int_active (struct nitrox_device*) ; 

__attribute__((used)) static irqreturn_t nps_core_int_isr(int irq, void *data)
{
	struct nitrox_device *ndev = data;

	clear_nps_core_int_active(ndev);

	return IRQ_HANDLED;
}