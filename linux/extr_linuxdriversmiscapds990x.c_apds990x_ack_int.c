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
struct i2c_client {int dummy; } ;
struct apds990x_chip {struct i2c_client* client; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int APDS990X_INT_ACK_ALS ; 
 int APDS990X_INT_ACK_BOTH ; 
 int APDS990X_INT_ACK_PS ; 
#define  APDS990X_ST_AINT 129 
#define  APDS990X_ST_PINT 128 
 int APDS990x_CMD ; 
 int APDS990x_CMD_TYPE_SPE ; 
 scalar_t__ i2c_smbus_read_byte_data (struct i2c_client*,int) ; 

__attribute__((used)) static int apds990x_ack_int(struct apds990x_chip *chip, u8 mode)
{
	struct i2c_client *client = chip->client;
	s32 ret;
	u8 reg = APDS990x_CMD | APDS990x_CMD_TYPE_SPE;

	switch (mode & (APDS990X_ST_AINT | APDS990X_ST_PINT)) {
	case APDS990X_ST_AINT:
		reg |= APDS990X_INT_ACK_ALS;
		break;
	case APDS990X_ST_PINT:
		reg |= APDS990X_INT_ACK_PS;
		break;
	default:
		reg |= APDS990X_INT_ACK_BOTH;
		break;
	}

	ret = i2c_smbus_read_byte_data(client, reg);
	return (int)ret;
}