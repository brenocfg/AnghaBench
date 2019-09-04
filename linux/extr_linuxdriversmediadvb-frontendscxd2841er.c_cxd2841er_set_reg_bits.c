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
struct cxd2841er_priv {int dummy; } ;

/* Variables and functions */
 int cxd2841er_read_reg (struct cxd2841er_priv*,int,int,int*) ; 
 int cxd2841er_write_reg (struct cxd2841er_priv*,int,int,int) ; 

__attribute__((used)) static int cxd2841er_set_reg_bits(struct cxd2841er_priv *priv,
				  u8 addr, u8 reg, u8 data, u8 mask)
{
	int res;
	u8 rdata;

	if (mask != 0xff) {
		res = cxd2841er_read_reg(priv, addr, reg, &rdata);
		if (res)
			return res;
		data = ((data & mask) | (rdata & (mask ^ 0xFF)));
	}
	return cxd2841er_write_reg(priv, addr, reg, data);
}