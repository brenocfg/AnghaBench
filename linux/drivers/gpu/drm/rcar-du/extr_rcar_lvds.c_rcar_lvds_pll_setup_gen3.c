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
struct rcar_lvds {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LVDPLLCR ; 
 int /*<<< orphan*/  LVDPLLCR_PLLDIVCNT_128M ; 
 int /*<<< orphan*/  LVDPLLCR_PLLDIVCNT_148M ; 
 int /*<<< orphan*/  LVDPLLCR_PLLDIVCNT_42M ; 
 int /*<<< orphan*/  LVDPLLCR_PLLDIVCNT_85M ; 
 int /*<<< orphan*/  rcar_lvds_write (struct rcar_lvds*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rcar_lvds_pll_setup_gen3(struct rcar_lvds *lvds, unsigned int freq)
{
	u32 val;

	if (freq < 42000000)
		val = LVDPLLCR_PLLDIVCNT_42M;
	else if (freq < 85000000)
		val = LVDPLLCR_PLLDIVCNT_85M;
	else if (freq < 128000000)
		val = LVDPLLCR_PLLDIVCNT_128M;
	else
		val = LVDPLLCR_PLLDIVCNT_148M;

	rcar_lvds_write(lvds, LVDPLLCR, val);
}