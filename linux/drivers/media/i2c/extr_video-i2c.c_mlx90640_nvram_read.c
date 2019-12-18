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
struct video_i2c_data {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int regmap_bulk_read (int /*<<< orphan*/ ,int,void*,size_t) ; 

__attribute__((used)) static int mlx90640_nvram_read(void *priv, unsigned int offset, void *val,
			     size_t bytes)
{
	struct video_i2c_data *data = priv;

	return regmap_bulk_read(data->regmap, 0x2400 + offset, val, bytes);
}