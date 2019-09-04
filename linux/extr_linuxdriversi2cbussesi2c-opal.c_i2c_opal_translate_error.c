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

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int ENXIO ; 
 int ETIMEDOUT ; 
#define  OPAL_I2C_ARBT_LOST 133 
#define  OPAL_I2C_NACK_RCVD 132 
#define  OPAL_I2C_STOP_ERR 131 
#define  OPAL_I2C_TIMEOUT 130 
#define  OPAL_NO_MEM 129 
#define  OPAL_PARAMETER 128 

__attribute__((used)) static int i2c_opal_translate_error(int rc)
{
	switch (rc) {
	case OPAL_NO_MEM:
		return -ENOMEM;
	case OPAL_PARAMETER:
		return -EINVAL;
	case OPAL_I2C_ARBT_LOST:
		return -EAGAIN;
	case OPAL_I2C_TIMEOUT:
		return -ETIMEDOUT;
	case OPAL_I2C_NACK_RCVD:
		return -ENXIO;
	case OPAL_I2C_STOP_ERR:
		return -EBUSY;
	default:
		return -EIO;
	}
}