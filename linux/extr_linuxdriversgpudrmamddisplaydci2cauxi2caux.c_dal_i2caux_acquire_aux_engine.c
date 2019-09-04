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
struct i2caux {struct aux_engine** aux_engines; } ;
struct ddc {int dummy; } ;
struct TYPE_4__ {TYPE_1__* funcs; } ;
struct aux_engine {TYPE_2__ base; } ;
typedef  enum gpio_ddc_line { ____Placeholder_gpio_ddc_line } gpio_ddc_line ;
struct TYPE_3__ {int /*<<< orphan*/  (* acquire ) (TYPE_2__*,struct ddc*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  get_hw_supported_ddc_line (struct ddc*,int*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,struct ddc*) ; 

struct aux_engine *dal_i2caux_acquire_aux_engine(
	struct i2caux *i2caux,
	struct ddc *ddc)
{
	enum gpio_ddc_line line;
	struct aux_engine *engine;

	if (!get_hw_supported_ddc_line(ddc, &line))
		return NULL;

	engine = i2caux->aux_engines[line];

	if (!engine)
		return NULL;

	if (!engine->base.funcs->acquire(&engine->base, ddc))
		return NULL;

	return engine;
}