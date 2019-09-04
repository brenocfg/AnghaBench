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
struct ddc {int dummy; } ;
struct aux_engine {struct ddc* ddc; TYPE_1__* funcs; } ;
typedef  enum gpio_result { ____Placeholder_gpio_result } gpio_result ;
struct TYPE_2__ {int /*<<< orphan*/  (* acquire_engine ) (struct aux_engine*) ;int /*<<< orphan*/  (* is_engine_available ) (struct aux_engine*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_DDC_CONFIG_TYPE_MODE_AUX ; 
 int /*<<< orphan*/  GPIO_MODE_HARDWARE ; 
 int GPIO_RESULT_OK ; 
 int /*<<< orphan*/  dal_ddc_close (struct ddc*) ; 
 int dal_ddc_open (struct ddc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct aux_engine*) ; 
 int /*<<< orphan*/  stub2 (struct aux_engine*) ; 

__attribute__((used)) static bool acquire(
	struct aux_engine *engine,
	struct ddc *ddc)
{

	enum gpio_result result;

	if (engine->funcs->is_engine_available) {
		/*check whether SW could use the engine*/
		if (!engine->funcs->is_engine_available(engine))
			return false;
	}

	result = dal_ddc_open(ddc, GPIO_MODE_HARDWARE,
		GPIO_DDC_CONFIG_TYPE_MODE_AUX);

	if (result != GPIO_RESULT_OK)
		return false;

	if (!engine->funcs->acquire_engine(engine)) {
		dal_ddc_close(ddc);
		return false;
	}

	engine->ddc = ddc;

	return true;
}