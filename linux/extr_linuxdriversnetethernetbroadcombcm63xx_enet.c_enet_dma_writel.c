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
struct bcm_enet_priv {int dummy; } ;

/* Variables and functions */
 scalar_t__* bcm_enet_shared_base ; 
 int /*<<< orphan*/  bcm_writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void enet_dma_writel(struct bcm_enet_priv *priv,
				       u32 val, u32 off)
{
	bcm_writel(val, bcm_enet_shared_base[0] + off);
}