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
struct atmel_hlcdc_layer {TYPE_1__* desc; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {scalar_t__ clut_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void atmel_hlcdc_layer_write_clut(struct atmel_hlcdc_layer *layer,
						unsigned int c, u32 val)
{
	regmap_write(layer->regmap,
		     layer->desc->clut_offset + c * sizeof(u32),
		     val);
}