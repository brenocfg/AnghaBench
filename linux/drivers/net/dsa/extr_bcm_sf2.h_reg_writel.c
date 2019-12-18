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
typedef  size_t u16 ;
struct bcm_sf2_priv {scalar_t__* reg_offsets; scalar_t__ reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void reg_writel(struct bcm_sf2_priv *priv, u32 val, u16 off)
{
	writel_relaxed(val, priv->reg + priv->reg_offsets[off]);
}