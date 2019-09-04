#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct hw_gpio_pin {TYPE_3__* funcs; } ;
struct TYPE_5__ {TYPE_1__* funcs; } ;
struct gpio_service {int /*<<< orphan*/  ctx; TYPE_2__ factory; int /*<<< orphan*/ * busyness; } ;
typedef  enum gpio_result { ____Placeholder_gpio_result } gpio_result ;
typedef  enum gpio_mode { ____Placeholder_gpio_mode } gpio_mode ;
typedef  enum gpio_id { ____Placeholder_gpio_id } gpio_id ;
struct TYPE_6__ {int /*<<< orphan*/  (* open ) (struct hw_gpio_pin*,int) ;} ;
struct TYPE_4__ {struct hw_gpio_pin* (* create_gsl ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;struct hw_gpio_pin* (* create_sync ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* define_hpd_registers ) (struct hw_gpio_pin*,int /*<<< orphan*/ ) ;struct hw_gpio_pin* (* create_hpd ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;struct hw_gpio_pin* (* create_generic ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* define_ddc_registers ) (struct hw_gpio_pin*,int /*<<< orphan*/ ) ;struct hw_gpio_pin* (* create_ddc_clock ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;struct hw_gpio_pin* (* create_ddc_data ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_CRITICAL (int) ; 
#define  GPIO_ID_DDC_CLOCK 133 
#define  GPIO_ID_DDC_DATA 132 
#define  GPIO_ID_GENERIC 131 
#define  GPIO_ID_GSL 130 
#define  GPIO_ID_HPD 129 
#define  GPIO_ID_SYNC 128 
 int GPIO_RESULT_DEVICE_BUSY ; 
 int GPIO_RESULT_NON_SPECIFIC_ERROR ; 
 int GPIO_RESULT_OK ; 
 int GPIO_RESULT_OPEN_FAILED ; 
 int /*<<< orphan*/  dal_gpio_service_close (struct gpio_service*,struct hw_gpio_pin**) ; 
 scalar_t__ is_pin_busy (struct gpio_service*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pin_busy (struct gpio_service*,int,int /*<<< orphan*/ ) ; 
 struct hw_gpio_pin* stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub10 (struct hw_gpio_pin*,int) ; 
 int /*<<< orphan*/  stub2 (struct hw_gpio_pin*,int /*<<< orphan*/ ) ; 
 struct hw_gpio_pin* stub3 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct hw_gpio_pin*,int /*<<< orphan*/ ) ; 
 struct hw_gpio_pin* stub5 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct hw_gpio_pin* stub6 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (struct hw_gpio_pin*,int /*<<< orphan*/ ) ; 
 struct hw_gpio_pin* stub8 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct hw_gpio_pin* stub9 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

enum gpio_result dal_gpio_service_open(
	struct gpio_service *service,
	enum gpio_id id,
	uint32_t en,
	enum gpio_mode mode,
	struct hw_gpio_pin **ptr)
{
	struct hw_gpio_pin *pin;

	if (!service->busyness[id]) {
		ASSERT_CRITICAL(false);
		return GPIO_RESULT_OPEN_FAILED;
	}

	if (is_pin_busy(service, id, en)) {
		ASSERT_CRITICAL(false);
		return GPIO_RESULT_DEVICE_BUSY;
	}

	switch (id) {
	case GPIO_ID_DDC_DATA:
		pin = service->factory.funcs->create_ddc_data(
			service->ctx, id, en);
		service->factory.funcs->define_ddc_registers(pin, en);
	break;
	case GPIO_ID_DDC_CLOCK:
		pin = service->factory.funcs->create_ddc_clock(
			service->ctx, id, en);
		service->factory.funcs->define_ddc_registers(pin, en);
	break;
	case GPIO_ID_GENERIC:
		pin = service->factory.funcs->create_generic(
			service->ctx, id, en);
	break;
	case GPIO_ID_HPD:
		pin = service->factory.funcs->create_hpd(
			service->ctx, id, en);
		service->factory.funcs->define_hpd_registers(pin, en);
	break;
	case GPIO_ID_SYNC:
		pin = service->factory.funcs->create_sync(
			service->ctx, id, en);
	break;
	case GPIO_ID_GSL:
		pin = service->factory.funcs->create_gsl(
			service->ctx, id, en);
	break;
	default:
		ASSERT_CRITICAL(false);
		return GPIO_RESULT_NON_SPECIFIC_ERROR;
	}

	if (!pin) {
		ASSERT_CRITICAL(false);
		return GPIO_RESULT_NON_SPECIFIC_ERROR;
	}

	if (!pin->funcs->open(pin, mode)) {
		ASSERT_CRITICAL(false);
		dal_gpio_service_close(service, &pin);
		return GPIO_RESULT_OPEN_FAILED;
	}

	set_pin_busy(service, id, en);
	*ptr = pin;
	return GPIO_RESULT_OK;
}