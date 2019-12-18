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
struct rcar_lvds {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __rcar_lvds_pll_setup_d3_e3 (struct rcar_lvds*,unsigned int,int) ; 

__attribute__((used)) static void rcar_lvds_pll_setup_d3_e3(struct rcar_lvds *lvds, unsigned int freq)
{
	__rcar_lvds_pll_setup_d3_e3(lvds, freq, false);
}