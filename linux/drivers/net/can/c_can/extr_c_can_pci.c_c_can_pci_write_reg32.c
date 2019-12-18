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
struct c_can_priv {int /*<<< orphan*/  (* write_reg ) (struct c_can_priv const*,int,int) ;} ;
typedef  enum reg { ____Placeholder_reg } reg ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct c_can_priv const*,int,int) ; 
 int /*<<< orphan*/  stub2 (struct c_can_priv const*,int,int) ; 

__attribute__((used)) static void c_can_pci_write_reg32(const struct c_can_priv *priv, enum reg index,
		u32 val)
{
	priv->write_reg(priv, index + 1, val >> 16);
	priv->write_reg(priv, index, val);
}