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
struct hw_generic {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  dal_hw_gpio_destruct (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dal_hw_generic_destruct(
	struct hw_generic *pin)
{
	dal_hw_gpio_destruct(&pin->base);
}