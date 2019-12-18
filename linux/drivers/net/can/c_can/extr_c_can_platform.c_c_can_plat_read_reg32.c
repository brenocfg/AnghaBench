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
struct c_can_priv {int (* read_reg ) (struct c_can_priv const*,int) ;} ;
typedef  enum reg { ____Placeholder_reg } reg ;

/* Variables and functions */
 int stub1 (struct c_can_priv const*,int) ; 
 int stub2 (struct c_can_priv const*,int) ; 

__attribute__((used)) static u32 c_can_plat_read_reg32(const struct c_can_priv *priv, enum reg index)
{
	u32 val;

	val = priv->read_reg(priv, index);
	val |= ((u32) priv->read_reg(priv, index + 1)) << 16;

	return val;
}