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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fhc_led_types ; 
 int sunfire_led_generic_probe (struct platform_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sunfire_fhc_led_probe(struct platform_device *pdev)
{
	return sunfire_led_generic_probe(pdev, fhc_led_types);
}