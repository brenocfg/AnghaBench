#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bus_type {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int* aqm; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 TYPE_1__* ap_configuration ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static ssize_t ap_usage_domain_mask_show(struct bus_type *bus, char *buf)
{
	if (!ap_configuration)	/* QCI not supported */
		return snprintf(buf, PAGE_SIZE, "not supported\n");

	return snprintf(buf, PAGE_SIZE,
			"0x%08x%08x%08x%08x%08x%08x%08x%08x\n",
			ap_configuration->aqm[0], ap_configuration->aqm[1],
			ap_configuration->aqm[2], ap_configuration->aqm[3],
			ap_configuration->aqm[4], ap_configuration->aqm[5],
			ap_configuration->aqm[6], ap_configuration->aqm[7]);
}