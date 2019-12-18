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
struct video_i2c_data {TYPE_1__* chip; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  buffer_size; } ;

/* Variables and functions */
 int regmap_bulk_read (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx90640_xfer(struct video_i2c_data *data, char *buf)
{
	return regmap_bulk_read(data->regmap, 0x400, buf,
				data->chip->buffer_size);
}