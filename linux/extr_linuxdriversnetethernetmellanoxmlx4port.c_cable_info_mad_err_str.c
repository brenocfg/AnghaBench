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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
#define  CABLE_INF_I2C_ADDR 136 
#define  CABLE_INF_I2C_BUSY 135 
#define  CABLE_INF_INV_ADDR 134 
#define  CABLE_INF_INV_PORT 133 
#define  CABLE_INF_NOT_CONN 132 
#define  CABLE_INF_NO_EEPRM 131 
#define  CABLE_INF_OP_NOSUP 130 
#define  CABLE_INF_PAGE_ERR 129 
#define  CABLE_INF_QSFP_VIO 128 
 int MAD_STATUS_2_CABLE_ERR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline const char *cable_info_mad_err_str(u16 mad_status)
{
	u8 err = MAD_STATUS_2_CABLE_ERR(mad_status);

	switch (err) {
	case CABLE_INF_INV_PORT:
		return "invalid port selected";
	case CABLE_INF_OP_NOSUP:
		return "operation not supported for this port (the port is of type CX4 or internal)";
	case CABLE_INF_NOT_CONN:
		return "cable is not connected";
	case CABLE_INF_NO_EEPRM:
		return "the connected cable has no EPROM (passive copper cable)";
	case CABLE_INF_PAGE_ERR:
		return "page number is greater than 15";
	case CABLE_INF_INV_ADDR:
		return "invalid device_address or size (that is, size equals 0 or address+size is greater than 256)";
	case CABLE_INF_I2C_ADDR:
		return "invalid I2C slave address";
	case CABLE_INF_QSFP_VIO:
		return "at least one cable violates the QSFP specification and ignores the modsel signal";
	case CABLE_INF_I2C_BUSY:
		return "I2C bus is constantly busy";
	}
	return "Unknown Error";
}