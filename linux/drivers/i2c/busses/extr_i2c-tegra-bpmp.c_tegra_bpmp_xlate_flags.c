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
typedef  int u16 ;

/* Variables and functions */
 int EINVAL ; 
 int I2C_M_IGNORE_NAK ; 
 int I2C_M_NOSTART ; 
 int I2C_M_NO_RD_ACK ; 
 int I2C_M_RD ; 
 int I2C_M_RECV_LEN ; 
 int I2C_M_REV_DIR_ADDR ; 
 int I2C_M_STOP ; 
 int I2C_M_TEN ; 
 int SERIALI2C_IGNORE_NAK ; 
 int SERIALI2C_NOSTART ; 
 int SERIALI2C_NO_RD_ACK ; 
 int SERIALI2C_RD ; 
 int SERIALI2C_RECV_LEN ; 
 int SERIALI2C_REV_DIR_ADDR ; 
 int SERIALI2C_STOP ; 
 int SERIALI2C_TEN ; 

__attribute__((used)) static int tegra_bpmp_xlate_flags(u16 flags, u16 *out)
{
	if (flags & I2C_M_TEN) {
		*out |= SERIALI2C_TEN;
		flags &= ~I2C_M_TEN;
	}

	if (flags & I2C_M_RD) {
		*out |= SERIALI2C_RD;
		flags &= ~I2C_M_RD;
	}

	if (flags & I2C_M_STOP) {
		*out |= SERIALI2C_STOP;
		flags &= ~I2C_M_STOP;
	}

	if (flags & I2C_M_NOSTART) {
		*out |= SERIALI2C_NOSTART;
		flags &= ~I2C_M_NOSTART;
	}

	if (flags & I2C_M_REV_DIR_ADDR) {
		*out |= SERIALI2C_REV_DIR_ADDR;
		flags &= ~I2C_M_REV_DIR_ADDR;
	}

	if (flags & I2C_M_IGNORE_NAK) {
		*out |= SERIALI2C_IGNORE_NAK;
		flags &= ~I2C_M_IGNORE_NAK;
	}

	if (flags & I2C_M_NO_RD_ACK) {
		*out |= SERIALI2C_NO_RD_ACK;
		flags &= ~I2C_M_NO_RD_ACK;
	}

	if (flags & I2C_M_RECV_LEN) {
		*out |= SERIALI2C_RECV_LEN;
		flags &= ~I2C_M_RECV_LEN;
	}

	return (flags != 0) ? -EINVAL : 0;
}