#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct regmap {int dummy; } ;
struct atmel_hlcdc_layer_desc {int dummy; } ;
struct atmel_hlcdc_layer {struct regmap* regmap; struct atmel_hlcdc_layer_desc const* desc; } ;

/* Variables and functions */

__attribute__((used)) static inline void atmel_hlcdc_layer_init(struct atmel_hlcdc_layer *layer,
				const struct atmel_hlcdc_layer_desc *desc,
				struct regmap *regmap)
{
	layer->desc = desc;
	layer->regmap = regmap;
}