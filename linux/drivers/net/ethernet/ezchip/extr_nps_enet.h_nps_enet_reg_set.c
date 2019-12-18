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
struct nps_enet_priv {scalar_t__ regs_base; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite32be (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void nps_enet_reg_set(struct nps_enet_priv *priv,
				    s32 reg, s32 value)
{
	iowrite32be(value, priv->regs_base + reg);
}