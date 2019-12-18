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
struct pm80x_subchip {scalar_t__ gpadc_page; scalar_t__ power_page; } ;
struct pm80x_chip {struct pm80x_subchip* subchip; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_unregister_device (scalar_t__) ; 

__attribute__((used)) static void pm800_pages_exit(struct pm80x_chip *chip)
{
	struct pm80x_subchip *subchip;

	subchip = chip->subchip;

	if (subchip && subchip->power_page)
		i2c_unregister_device(subchip->power_page);

	if (subchip && subchip->gpadc_page)
		i2c_unregister_device(subchip->gpadc_page);
}