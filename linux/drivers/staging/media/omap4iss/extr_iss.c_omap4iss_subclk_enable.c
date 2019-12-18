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
struct iss_device {int subclk_resources; } ;
typedef  enum iss_subclk_resource { ____Placeholder_iss_subclk_resource } iss_subclk_resource ;

/* Variables and functions */
 int __iss_subclk_update (struct iss_device*) ; 

int omap4iss_subclk_enable(struct iss_device *iss,
			   enum iss_subclk_resource res)
{
	iss->subclk_resources |= res;

	return __iss_subclk_update(iss);
}