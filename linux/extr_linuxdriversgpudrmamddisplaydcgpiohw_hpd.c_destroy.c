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
struct hw_hpd {int dummy; } ;
struct hw_gpio_pin {int dummy; } ;

/* Variables and functions */
 struct hw_hpd* HW_HPD_FROM_BASE (struct hw_gpio_pin*) ; 
 int /*<<< orphan*/  destruct (struct hw_hpd*) ; 
 int /*<<< orphan*/  kfree (struct hw_hpd*) ; 

__attribute__((used)) static void destroy(
	struct hw_gpio_pin **ptr)
{
	struct hw_hpd *hpd = HW_HPD_FROM_BASE(*ptr);

	destruct(hpd);

	kfree(hpd);

	*ptr = NULL;
}