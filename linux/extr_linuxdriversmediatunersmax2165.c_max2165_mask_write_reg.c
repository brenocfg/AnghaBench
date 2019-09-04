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
typedef  int /*<<< orphan*/  u8 ;
struct max2165_priv {int dummy; } ;

/* Variables and functions */
 int max2165_read_reg (struct max2165_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int max2165_write_reg (struct max2165_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max2165_mask_write_reg(struct max2165_priv *priv, u8 reg,
	u8 mask, u8 data)
{
	int ret;
	u8 v;

	data &= mask;
	ret = max2165_read_reg(priv, reg, &v);
	if (ret != 0)
		return ret;
	v &= ~mask;
	v |= data;
	ret = max2165_write_reg(priv, reg, v);

	return ret;
}