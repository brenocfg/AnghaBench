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
typedef  int /*<<< orphan*/  u32 ;
struct atmel_hlcdc_layer {TYPE_1__* desc; } ;
struct TYPE_2__ {scalar_t__ cfgs_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  atmel_hlcdc_layer_write_reg (struct atmel_hlcdc_layer*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void atmel_hlcdc_layer_write_cfg(struct atmel_hlcdc_layer *layer,
					       unsigned int cfgid, u32 val)
{
	atmel_hlcdc_layer_write_reg(layer,
				    layer->desc->cfgs_offset +
				    (cfgid * sizeof(u32)), val);
}