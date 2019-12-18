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
struct ddc_service {int dongle_type; } ;
typedef  enum display_dongle_type { ____Placeholder_display_dongle_type } display_dongle_type ;

/* Variables and functions */

void ddc_service_set_dongle_type(struct ddc_service *ddc,
		enum display_dongle_type dongle_type)
{
	ddc->dongle_type = dongle_type;
}