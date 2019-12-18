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
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  aspm_disable_all (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  aspm_enable (struct hfi1_devdata*) ; 

void aspm_exit(struct hfi1_devdata *dd)
{
	aspm_disable_all(dd);

	/* Turn on ASPM on exit to conserve power */
	aspm_enable(dd);
}