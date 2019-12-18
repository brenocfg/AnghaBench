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
typedef  int u8 ;
struct helene_priv {int dummy; } ;

/* Variables and functions */
 int helene_read_reg (struct helene_priv*,int,int*) ; 
 int helene_write_reg (struct helene_priv*,int,int) ; 

__attribute__((used)) static int helene_set_reg_bits(struct helene_priv *priv,
		u8 reg, u8 data, u8 mask)
{
	int res;
	u8 rdata;

	if (mask != 0xff) {
		res = helene_read_reg(priv, reg, &rdata);
		if (res != 0)
			return res;
		data = ((data & mask) | (rdata & (mask ^ 0xFF)));
	}
	return helene_write_reg(priv, reg, data);
}