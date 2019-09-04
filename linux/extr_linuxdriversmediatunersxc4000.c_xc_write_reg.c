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
typedef  int u16 ;
struct xc4000_priv {int dummy; } ;

/* Variables and functions */
 int xc_send_i2c_data (struct xc4000_priv*,int*,int) ; 

__attribute__((used)) static int xc_write_reg(struct xc4000_priv *priv, u16 regAddr, u16 i2cData)
{
	u8 buf[4];
	int result;

	buf[0] = (regAddr >> 8) & 0xFF;
	buf[1] = regAddr & 0xFF;
	buf[2] = (i2cData >> 8) & 0xFF;
	buf[3] = i2cData & 0xFF;
	result = xc_send_i2c_data(priv, buf, 4);

	return result;
}