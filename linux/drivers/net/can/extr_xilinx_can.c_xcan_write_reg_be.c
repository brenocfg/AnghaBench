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
struct xcan_priv {int reg_base; } ;
typedef  enum xcan_reg { ____Placeholder_xcan_reg } xcan_reg ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite32be (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xcan_write_reg_be(const struct xcan_priv *priv, enum xcan_reg reg,
			      u32 val)
{
	iowrite32be(val, priv->reg_base + reg);
}