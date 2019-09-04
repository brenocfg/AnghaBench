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
struct r820t_priv {int* regs; } ;

/* Variables and functions */
 int EINVAL ; 
 int NUM_REGS ; 
 scalar_t__ REG_SHADOW_START ; 

__attribute__((used)) static int r820t_read_cache_reg(struct r820t_priv *priv, int reg)
{
	reg -= REG_SHADOW_START;

	if (reg >= 0 && reg < NUM_REGS)
		return priv->regs[reg];
	else
		return -EINVAL;
}