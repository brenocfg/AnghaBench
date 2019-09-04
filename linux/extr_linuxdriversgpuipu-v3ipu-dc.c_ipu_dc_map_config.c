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
typedef  enum ipu_dc_map { ____Placeholder_ipu_dc_map } ipu_dc_map ;

/* Variables and functions */
 scalar_t__ DC_MAP_CONF_PTR (int) ; 
 scalar_t__ DC_MAP_CONF_VAL (int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void ipu_dc_map_config(struct ipu_dc_priv *priv, enum ipu_dc_map map,
		int byte_num, int offset, int mask)
{
	int ptr = map * 3 + byte_num;
	u32 reg;

	reg = readl(priv->dc_reg + DC_MAP_CONF_VAL(ptr));
	reg &= ~(0xffff << (16 * (ptr & 0x1)));
	reg |= ((offset << 8) | mask) << (16 * (ptr & 0x1));
	writel(reg, priv->dc_reg + DC_MAP_CONF_VAL(ptr));

	reg = readl(priv->dc_reg + DC_MAP_CONF_PTR(map));
	reg &= ~(0x1f << ((16 * (map & 0x1)) + (5 * byte_num)));
	reg |= ptr << ((16 * (map & 0x1)) + (5 * byte_num));
	writel(reg, priv->dc_reg + DC_MAP_CONF_PTR(map));
}