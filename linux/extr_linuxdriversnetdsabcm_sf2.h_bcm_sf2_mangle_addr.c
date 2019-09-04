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
struct bcm_sf2_priv {int core_reg_align; } ;

/* Variables and functions */

__attribute__((used)) static inline u32 bcm_sf2_mangle_addr(struct bcm_sf2_priv *priv, u32 off)
{
	return off << priv->core_reg_align;
}