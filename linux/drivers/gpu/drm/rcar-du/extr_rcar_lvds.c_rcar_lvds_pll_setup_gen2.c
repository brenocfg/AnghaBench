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
typedef  int u32 ;
struct rcar_lvds {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LVDPLLCR ; 
 int LVDPLLCR_CEEN ; 
 int LVDPLLCR_COSEL ; 
 int LVDPLLCR_PLLDLYCNT_121M ; 
 int LVDPLLCR_PLLDLYCNT_150M ; 
 int LVDPLLCR_PLLDLYCNT_38M ; 
 int LVDPLLCR_PLLDLYCNT_60M ; 
 int /*<<< orphan*/  rcar_lvds_write (struct rcar_lvds*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rcar_lvds_pll_setup_gen2(struct rcar_lvds *lvds, unsigned int freq)
{
	u32 val;

	if (freq < 39000000)
		val = LVDPLLCR_CEEN | LVDPLLCR_COSEL | LVDPLLCR_PLLDLYCNT_38M;
	else if (freq < 61000000)
		val = LVDPLLCR_CEEN | LVDPLLCR_COSEL | LVDPLLCR_PLLDLYCNT_60M;
	else if (freq < 121000000)
		val = LVDPLLCR_CEEN | LVDPLLCR_COSEL | LVDPLLCR_PLLDLYCNT_121M;
	else
		val = LVDPLLCR_PLLDLYCNT_150M;

	rcar_lvds_write(lvds, LVDPLLCR, val);
}