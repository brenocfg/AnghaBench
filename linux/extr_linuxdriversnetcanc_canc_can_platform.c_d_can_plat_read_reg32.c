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
struct c_can_priv {scalar_t__* regs; scalar_t__ base; } ;
typedef  enum reg { ____Placeholder_reg } reg ;

/* Variables and functions */
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static u32 d_can_plat_read_reg32(const struct c_can_priv *priv, enum reg index)
{
	return readl(priv->base + priv->regs[index]);
}