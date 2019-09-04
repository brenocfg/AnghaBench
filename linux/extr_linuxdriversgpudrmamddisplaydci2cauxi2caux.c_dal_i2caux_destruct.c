#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct i2caux {TYPE_6__** i2c_sw_engines; TYPE_7__** i2c_hw_engines; TYPE_8__** aux_engines; TYPE_9__* i2c_generic_sw_engine; TYPE_10__* i2c_generic_hw_engine; } ;
struct TYPE_20__ {TYPE_2__* funcs; } ;
struct TYPE_19__ {TYPE_3__* funcs; } ;
struct TYPE_18__ {TYPE_4__* funcs; } ;
struct TYPE_17__ {TYPE_5__* funcs; } ;
struct TYPE_16__ {int /*<<< orphan*/  (* destroy ) (TYPE_6__**) ;} ;
struct TYPE_15__ {int /*<<< orphan*/  (* destroy ) (TYPE_7__**) ;} ;
struct TYPE_14__ {int /*<<< orphan*/  (* destroy ) (TYPE_8__**) ;} ;
struct TYPE_13__ {int /*<<< orphan*/  (* destroy ) (TYPE_9__**) ;} ;
struct TYPE_12__ {int /*<<< orphan*/  (* destroy ) (TYPE_10__**) ;} ;
struct TYPE_11__ {TYPE_1__* funcs; } ;

/* Variables and functions */
 size_t GPIO_DDC_LINE_COUNT ; 
 int /*<<< orphan*/  stub1 (TYPE_10__**) ; 
 int /*<<< orphan*/  stub2 (TYPE_9__**) ; 
 int /*<<< orphan*/  stub3 (TYPE_8__**) ; 
 int /*<<< orphan*/  stub4 (TYPE_7__**) ; 
 int /*<<< orphan*/  stub5 (TYPE_6__**) ; 

void dal_i2caux_destruct(
	struct i2caux *i2caux)
{
	uint32_t i = 0;

	if (i2caux->i2c_generic_hw_engine)
		i2caux->i2c_generic_hw_engine->funcs->destroy(
			&i2caux->i2c_generic_hw_engine);

	if (i2caux->i2c_generic_sw_engine)
		i2caux->i2c_generic_sw_engine->funcs->destroy(
			&i2caux->i2c_generic_sw_engine);

	do {
		if (i2caux->aux_engines[i])
			i2caux->aux_engines[i]->funcs->destroy(
				&i2caux->aux_engines[i]);

		if (i2caux->i2c_hw_engines[i])
			i2caux->i2c_hw_engines[i]->funcs->destroy(
				&i2caux->i2c_hw_engines[i]);

		if (i2caux->i2c_sw_engines[i])
			i2caux->i2c_sw_engines[i]->funcs->destroy(
				&i2caux->i2c_sw_engines[i]);

		++i;
	} while (i < GPIO_DDC_LINE_COUNT);
}