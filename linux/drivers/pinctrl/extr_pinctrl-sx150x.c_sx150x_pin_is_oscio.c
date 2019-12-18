#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sx150x_pinctrl {TYPE_2__* data; } ;
struct TYPE_4__ {unsigned int npins; scalar_t__ model; TYPE_1__* pins; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ SX150X_789 ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool sx150x_pin_is_oscio(struct sx150x_pinctrl *pctl, unsigned int pin)
{
	if (pin >= pctl->data->npins)
		return false;

	/* OSCIO pin is only present in 789 devices */
	if (pctl->data->model != SX150X_789)
		return false;

	return !strcmp(pctl->data->pins[pin].name, "oscio");
}