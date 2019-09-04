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
typedef  scalar_t__ u32 ;
struct bcm_sf2_priv {scalar_t__ core; } ;

/* Variables and functions */
 scalar_t__ bcm_sf2_mangle_addr (struct bcm_sf2_priv*,scalar_t__) ; 
 scalar_t__ readl_relaxed (scalar_t__) ; 

__attribute__((used)) static inline u32 core_readl(struct bcm_sf2_priv *priv, u32 off)
{
	u32 tmp = bcm_sf2_mangle_addr(priv, off);
	return readl_relaxed(priv->core + tmp);
}