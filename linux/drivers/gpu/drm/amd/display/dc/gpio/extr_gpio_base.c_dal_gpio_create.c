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
struct TYPE_5__ {TYPE_1__* funcs; } ;
struct gpio_service {int /*<<< orphan*/  ctx; TYPE_2__ factory; } ;
struct TYPE_6__ {int /*<<< orphan*/  hpd; int /*<<< orphan*/  generic; int /*<<< orphan*/  ddc; } ;
struct gpio {int id; int output_state; int /*<<< orphan*/ * pin; TYPE_3__ hw_container; struct gpio_service* service; int /*<<< orphan*/  mode; int /*<<< orphan*/  en; } ;
typedef  enum gpio_pin_output_state { ____Placeholder_gpio_pin_output_state } gpio_pin_output_state ;
typedef  enum gpio_id { ____Placeholder_gpio_id } gpio_id ;
struct TYPE_4__ {int /*<<< orphan*/  (* init_hpd ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* init_generic ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* init_ddc_data ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_CRITICAL (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  GPIO_ID_DDC_CLOCK 133 
#define  GPIO_ID_DDC_DATA 132 
#define  GPIO_ID_GENERIC 131 
#define  GPIO_ID_GSL 130 
#define  GPIO_ID_HPD 129 
#define  GPIO_ID_SYNC 128 
 int /*<<< orphan*/  GPIO_MODE_UNKNOWN ; 
 struct gpio* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

struct gpio *dal_gpio_create(
	struct gpio_service *service,
	enum gpio_id id,
	uint32_t en,
	enum gpio_pin_output_state output_state)
{
	struct gpio *gpio = kzalloc(sizeof(struct gpio), GFP_KERNEL);

	if (!gpio) {
		ASSERT_CRITICAL(false);
		return NULL;
	}

	gpio->service = service;
	gpio->pin = NULL;
	gpio->id = id;
	gpio->en = en;
	gpio->mode = GPIO_MODE_UNKNOWN;
	gpio->output_state = output_state;

	//initialize hw_container union based on id
	switch (gpio->id) {
	case GPIO_ID_DDC_DATA:
		gpio->service->factory.funcs->init_ddc_data(&gpio->hw_container.ddc, service->ctx, id, en);
		break;
	case GPIO_ID_DDC_CLOCK:
		gpio->service->factory.funcs->init_ddc_data(&gpio->hw_container.ddc, service->ctx, id, en);
		break;
	case GPIO_ID_GENERIC:
		gpio->service->factory.funcs->init_generic(&gpio->hw_container.generic, service->ctx, id, en);
		break;
	case GPIO_ID_HPD:
		gpio->service->factory.funcs->init_hpd(&gpio->hw_container.hpd, service->ctx, id, en);
		break;
	// TODO: currently gpio for sync and gsl does not get created, might need it later
	case GPIO_ID_SYNC:
		break;
	case GPIO_ID_GSL:
		break;
	default:
		ASSERT_CRITICAL(false);
		gpio->pin = NULL;
	}

	return gpio;
}