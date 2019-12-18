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
struct hisi_femac_priv {scalar_t__ glb_base; } ;

/* Variables and functions */
 scalar_t__ GLB_SOFT_RESET ; 
 int /*<<< orphan*/  SOFT_RESET_ALL ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int hisi_femac_port_reset(struct hisi_femac_priv *priv)
{
	u32 val;

	val = readl(priv->glb_base + GLB_SOFT_RESET);
	val |= SOFT_RESET_ALL;
	writel(val, priv->glb_base + GLB_SOFT_RESET);

	usleep_range(500, 800);

	val &= ~SOFT_RESET_ALL;
	writel(val, priv->glb_base + GLB_SOFT_RESET);

	return 0;
}