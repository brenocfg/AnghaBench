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

/* Variables and functions */
 int /*<<< orphan*/  LVDPLLCR_PLLDIVCNT_128M ; 
 int /*<<< orphan*/  LVDPLLCR_PLLDIVCNT_148M ; 
 int /*<<< orphan*/  LVDPLLCR_PLLDIVCNT_42M ; 
 int /*<<< orphan*/  LVDPLLCR_PLLDIVCNT_85M ; 

__attribute__((used)) static u32 rcar_lvds_lvdpllcr_gen3(unsigned int freq)
{
	if (freq < 42000)
		return LVDPLLCR_PLLDIVCNT_42M;
	else if (freq < 85000)
		return LVDPLLCR_PLLDIVCNT_85M;
	else if (freq < 128000)
		return LVDPLLCR_PLLDIVCNT_128M;
	else
		return LVDPLLCR_PLLDIVCNT_148M;
}