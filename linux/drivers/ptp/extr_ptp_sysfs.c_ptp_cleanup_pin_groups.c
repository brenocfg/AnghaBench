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
struct ptp_clock {int /*<<< orphan*/  pin_dev_attr; int /*<<< orphan*/  pin_attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void ptp_cleanup_pin_groups(struct ptp_clock *ptp)
{
	kfree(ptp->pin_attr);
	kfree(ptp->pin_dev_attr);
}