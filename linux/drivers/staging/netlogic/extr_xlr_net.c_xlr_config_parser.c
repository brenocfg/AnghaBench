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
struct xlr_net_priv {int /*<<< orphan*/  base_addr; } ;

/* Variables and functions */
 scalar_t__ R_L2TYPE_0 ; 
 scalar_t__ R_L3CTABLE ; 
 scalar_t__ R_L4CTABLE ; 
 scalar_t__ R_PARSERCONFIGREG ; 
 int /*<<< orphan*/  xlr_config_translate_table (struct xlr_net_priv*) ; 
 int /*<<< orphan*/  xlr_nae_wreg (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void xlr_config_parser(struct xlr_net_priv *priv)
{
	u32 val;

	/* Mark it as ETHERNET type */
	xlr_nae_wreg(priv->base_addr, R_L2TYPE_0, 0x01);

	/* Use 7bit CRChash for flow classification with 127 as CRC polynomial*/
	xlr_nae_wreg(priv->base_addr, R_PARSERCONFIGREG,
		     ((0x7f << 8) | (1 << 1)));

	/* configure the parser : L2 Type is configured in the bootloader */
	/* extract IP: src, dest protocol */
	xlr_nae_wreg(priv->base_addr, R_L3CTABLE,
		     (9 << 20) | (1 << 19) | (1 << 18) | (0x01 << 16) |
		     (0x0800 << 0));
	xlr_nae_wreg(priv->base_addr, R_L3CTABLE + 1,
		     (9 << 25) | (1 << 21) | (12 << 14) | (4 << 10) |
		     (16 << 4) | 4);

	/* Configure to extract SRC port and Dest port for TCP and UDP pkts */
	xlr_nae_wreg(priv->base_addr, R_L4CTABLE, 6);
	xlr_nae_wreg(priv->base_addr, R_L4CTABLE + 2, 17);
	val = ((0 << 21) | (2 << 17) | (2 << 11) | (2 << 7));
	xlr_nae_wreg(priv->base_addr, R_L4CTABLE + 1, val);
	xlr_nae_wreg(priv->base_addr, R_L4CTABLE + 3, val);

	xlr_config_translate_table(priv);
}