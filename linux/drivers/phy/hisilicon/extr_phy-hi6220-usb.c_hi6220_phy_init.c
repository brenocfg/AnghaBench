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
struct regmap {int dummy; } ;
struct hi6220_priv {struct regmap* reg; } ;

/* Variables and functions */
 int RST0_POR_PICOPHY ; 
 int RST0_USBOTG ; 
 int RST0_USBOTG_32K ; 
 int RST0_USBOTG_BUS ; 
 int /*<<< orphan*/  SC_PERIPH_RSTDIS0 ; 
 int /*<<< orphan*/  SC_PERIPH_RSTEN0 ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void hi6220_phy_init(struct hi6220_priv *priv)
{
	struct regmap *reg = priv->reg;
	u32 val, mask;

	val = RST0_USBOTG_BUS | RST0_POR_PICOPHY |
	      RST0_USBOTG | RST0_USBOTG_32K;
	mask = val;
	regmap_update_bits(reg, SC_PERIPH_RSTEN0, mask, val);
	regmap_update_bits(reg, SC_PERIPH_RSTDIS0, mask, val);
}