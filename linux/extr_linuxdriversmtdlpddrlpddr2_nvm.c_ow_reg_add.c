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
typedef  int u_long ;
struct pcm_int_data {int bus_width; } ;
struct map_info {int pfow_base; struct pcm_int_data* fldrv_priv; } ;

/* Variables and functions */

__attribute__((used)) static inline u_long ow_reg_add(struct map_info *map, u_long offset)
{
	u_long val = 0;
	struct pcm_int_data *pcm_data = map->fldrv_priv;

	val = map->pfow_base + offset*pcm_data->bus_width;

	return val;
}