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
struct xc5000_priv {int dummy; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int /*<<< orphan*/  XREG_BUSY ; 
 int /*<<< orphan*/  msleep (int) ; 
 int xc5000_readreg (struct xc5000_priv*,int /*<<< orphan*/ ,int*) ; 
 int xc_send_i2c_data (struct xc5000_priv*,int*,int) ; 

__attribute__((used)) static int xc_write_reg(struct xc5000_priv *priv, u16 reg_addr, u16 i2c_data)
{
	u8 buf[4];
	int watch_dog_timer = 100;
	int result;

	buf[0] = (reg_addr >> 8) & 0xFF;
	buf[1] = reg_addr & 0xFF;
	buf[2] = (i2c_data >> 8) & 0xFF;
	buf[3] = i2c_data & 0xFF;
	result = xc_send_i2c_data(priv, buf, 4);
	if (result == 0) {
		/* wait for busy flag to clear */
		while ((watch_dog_timer > 0) && (result == 0)) {
			result = xc5000_readreg(priv, XREG_BUSY, (u16 *)buf);
			if (result == 0) {
				if ((buf[0] == 0) && (buf[1] == 0)) {
					/* busy flag cleared */
					break;
				} else {
					msleep(5); /* wait 5 ms */
					watch_dog_timer--;
				}
			}
		}
	}
	if (watch_dog_timer <= 0)
		result = -EREMOTEIO;

	return result;
}