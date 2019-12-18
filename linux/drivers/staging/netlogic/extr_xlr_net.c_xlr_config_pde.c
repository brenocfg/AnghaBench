#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct xlr_net_priv {int /*<<< orphan*/  base_addr; TYPE_1__* nd; } ;
struct TYPE_2__ {int /*<<< orphan*/  cpu_mask; } ;

/* Variables and functions */
 scalar_t__ R_PDE_CLASS_0 ; 
 scalar_t__ R_PDE_CLASS_1 ; 
 scalar_t__ R_PDE_CLASS_2 ; 
 scalar_t__ R_PDE_CLASS_3 ; 
 int hweight32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xlr_nae_wreg (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void xlr_config_pde(struct xlr_net_priv *priv)
{
	int i = 0;
	u64 bkt_map = 0;

	/* Each core has 8 buckets(station) */
	for (i = 0; i < hweight32(priv->nd->cpu_mask); i++)
		bkt_map |= (0xff << (i * 8));

	xlr_nae_wreg(priv->base_addr, R_PDE_CLASS_0, (bkt_map & 0xffffffff));
	xlr_nae_wreg(priv->base_addr, R_PDE_CLASS_0 + 1,
		     ((bkt_map >> 32) & 0xffffffff));

	xlr_nae_wreg(priv->base_addr, R_PDE_CLASS_1, (bkt_map & 0xffffffff));
	xlr_nae_wreg(priv->base_addr, R_PDE_CLASS_1 + 1,
		     ((bkt_map >> 32) & 0xffffffff));

	xlr_nae_wreg(priv->base_addr, R_PDE_CLASS_2, (bkt_map & 0xffffffff));
	xlr_nae_wreg(priv->base_addr, R_PDE_CLASS_2 + 1,
		     ((bkt_map >> 32) & 0xffffffff));

	xlr_nae_wreg(priv->base_addr, R_PDE_CLASS_3, (bkt_map & 0xffffffff));
	xlr_nae_wreg(priv->base_addr, R_PDE_CLASS_3 + 1,
		     ((bkt_map >> 32) & 0xffffffff));
}