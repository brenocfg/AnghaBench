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
typedef  scalar_t__ u32 ;
struct vimc_pix_map {scalar_t__ code; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct vimc_pix_map const*) ; 
 struct vimc_pix_map const* vimc_pix_map_list ; 

const struct vimc_pix_map *vimc_pix_map_by_code(u32 code)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(vimc_pix_map_list); i++) {
		if (vimc_pix_map_list[i].code == code)
			return &vimc_pix_map_list[i];
	}
	return NULL;
}