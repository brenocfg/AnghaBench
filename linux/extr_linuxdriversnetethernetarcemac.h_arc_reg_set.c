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
struct arc_emac_priv {scalar_t__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 

__attribute__((used)) static inline void arc_reg_set(struct arc_emac_priv *priv, int reg, int value)
{
	iowrite32(value, priv->regs + reg * sizeof(int));
}