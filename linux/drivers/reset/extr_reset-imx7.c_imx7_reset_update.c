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
struct imx7_src_signal {int /*<<< orphan*/  bit; int /*<<< orphan*/  offset; } ;
struct imx7_src {int /*<<< orphan*/  regmap; struct imx7_src_signal* signals; } ;

/* Variables and functions */
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int imx7_reset_update(struct imx7_src *imx7src,
			     unsigned long id, unsigned int value)
{
	const struct imx7_src_signal *signal = &imx7src->signals[id];

	return regmap_update_bits(imx7src->regmap,
				  signal->offset, signal->bit, value);
}