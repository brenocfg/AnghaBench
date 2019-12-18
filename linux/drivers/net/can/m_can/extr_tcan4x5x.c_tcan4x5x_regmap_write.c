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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int regmap_spi_gather_write (void*,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static int tcan4x5x_regmap_write(void *context, const void *data, size_t count)
{
	u16 *reg = (u16 *)(data);
	const u32 *val = data + 4;

	return regmap_spi_gather_write(context, reg, 4, val, count - 4);
}