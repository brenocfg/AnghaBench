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
struct ipu_dc_priv {scalar_t__ dc_reg; } ;

/* Variables and functions */
 scalar_t__ DC_MAP_CONF_PTR (int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void ipu_dc_map_clear(struct ipu_dc_priv *priv, int map)
{
	u32 reg = readl(priv->dc_reg + DC_MAP_CONF_PTR(map));

	writel(reg & ~(0xffff << (16 * (map & 0x1))),
		     priv->dc_reg + DC_MAP_CONF_PTR(map));
}