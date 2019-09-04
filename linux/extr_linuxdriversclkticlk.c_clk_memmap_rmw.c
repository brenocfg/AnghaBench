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
typedef  int /*<<< orphan*/  u32 ;
struct clk_omap_reg {size_t index; scalar_t__ offset; scalar_t__ ptr; } ;
struct clk_iomap {scalar_t__ mem; scalar_t__ regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  _clk_rmw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct clk_iomap** clk_memmaps ; 
 int /*<<< orphan*/  regmap_update_bits (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clk_memmap_rmw(u32 val, u32 mask, const struct clk_omap_reg *reg)
{
	struct clk_iomap *io = clk_memmaps[reg->index];

	if (reg->ptr) {
		_clk_rmw(val, mask, reg->ptr);
	} else if (io->regmap) {
		regmap_update_bits(io->regmap, reg->offset, mask, val);
	} else {
		_clk_rmw(val, mask, io->mem + reg->offset);
	}
}