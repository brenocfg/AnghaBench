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
 int /*<<< orphan*/  aspm_exit (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  finish_chip_resources (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  free_cntrs (struct hfi1_devdata*) ; 
 int /*<<< orphan*/  free_rcverr (struct hfi1_devdata*) ; 

void hfi1_start_cleanup(struct hfi1_devdata *dd)
{
	aspm_exit(dd);
	free_cntrs(dd);
	free_rcverr(dd);
	finish_chip_resources(dd);
}