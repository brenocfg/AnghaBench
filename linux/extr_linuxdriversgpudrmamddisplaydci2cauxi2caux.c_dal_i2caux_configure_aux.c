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
typedef  union aux_config {int dummy; } aux_config ;
struct i2caux {TYPE_2__* funcs; } ;
struct ddc {int dummy; } ;
struct aux_engine {int /*<<< orphan*/  base; TYPE_1__* funcs; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* release_engine ) (struct i2caux*,int /*<<< orphan*/ *) ;struct aux_engine* (* acquire_aux_engine ) (struct i2caux*,struct ddc*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  (* configure ) (struct aux_engine*,union aux_config) ;} ;

/* Variables and functions */
 struct aux_engine* stub1 (struct i2caux*,struct ddc*) ; 
 int /*<<< orphan*/  stub2 (struct aux_engine*,union aux_config) ; 
 int /*<<< orphan*/  stub3 (struct i2caux*,int /*<<< orphan*/ *) ; 

void dal_i2caux_configure_aux(
	struct i2caux *i2caux,
	struct ddc *ddc,
	union aux_config cfg)
{
	struct aux_engine *engine =
		i2caux->funcs->acquire_aux_engine(i2caux, ddc);

	if (!engine)
		return;

	engine->funcs->configure(engine, cfg);

	i2caux->funcs->release_engine(i2caux, &engine->base);
}