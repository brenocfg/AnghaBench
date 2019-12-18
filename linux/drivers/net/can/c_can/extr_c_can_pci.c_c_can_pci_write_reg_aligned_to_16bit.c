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
typedef  int /*<<< orphan*/  u16 ;
struct c_can_priv {scalar_t__* regs; scalar_t__ base; } ;
typedef  enum reg { ____Placeholder_reg } reg ;

/* Variables and functions */
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void c_can_pci_write_reg_aligned_to_16bit(const struct c_can_priv *priv,
						enum reg index, u16 val)
{
	writew(val, priv->base + priv->regs[index]);
}