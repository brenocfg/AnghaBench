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
struct TYPE_2__ {struct gpio* hpd; struct gpio* generic; struct gpio* ddc; } ;
struct gpio {int id; TYPE_1__ hw_container; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_CRITICAL (int) ; 
#define  GPIO_ID_DDC_CLOCK 133 
#define  GPIO_ID_DDC_DATA 132 
#define  GPIO_ID_GENERIC 131 
#define  GPIO_ID_GSL 130 
#define  GPIO_ID_HPD 129 
#define  GPIO_ID_SYNC 128 
 int /*<<< orphan*/  dal_gpio_close (struct gpio*) ; 
 int /*<<< orphan*/  kfree (struct gpio*) ; 

void dal_gpio_destroy(
	struct gpio **gpio)
{
	if (!gpio || !*gpio) {
		ASSERT_CRITICAL(false);
		return;
	}

	dal_gpio_close(*gpio);

	switch ((*gpio)->id) {
	case GPIO_ID_DDC_DATA:
		kfree((*gpio)->hw_container.ddc);
		(*gpio)->hw_container.ddc = NULL;
		break;
	case GPIO_ID_DDC_CLOCK:
		//TODO: might want to change it to init_ddc_clock
		kfree((*gpio)->hw_container.ddc);
		(*gpio)->hw_container.ddc = NULL;
		break;
	case GPIO_ID_GENERIC:
		kfree((*gpio)->hw_container.generic);
		(*gpio)->hw_container.generic = NULL;
		break;
	case GPIO_ID_HPD:
		kfree((*gpio)->hw_container.hpd);
		(*gpio)->hw_container.hpd = NULL;
		break;
	// TODO: currently gpio for sync and gsl does not get created, might need it later
	case GPIO_ID_SYNC:
		break;
	case GPIO_ID_GSL:
		break;
	default:
		break;
	}

	kfree(*gpio);

	*gpio = NULL;
}