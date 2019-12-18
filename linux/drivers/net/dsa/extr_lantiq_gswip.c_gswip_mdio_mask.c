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
struct gswip_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gswip_mdio_r (struct gswip_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gswip_mdio_w (struct gswip_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gswip_mdio_mask(struct gswip_priv *priv, u32 clear, u32 set,
			    u32 offset)
{
	u32 val = gswip_mdio_r(priv, offset);

	val &= ~(clear);
	val |= set;
	gswip_mdio_w(priv, val, offset);
}