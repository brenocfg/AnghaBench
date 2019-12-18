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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 unsigned char DMARD10_MODE_OFF ; 
 unsigned char DMARD10_MODE_STANDBY ; 
 unsigned char DMARD10_REG_ACTR ; 
 int i2c_master_send (struct i2c_client*,unsigned char*,int) ; 

__attribute__((used)) static int dmard10_shutdown(struct i2c_client *client)
{
	unsigned char buffer[3];

	buffer[0] = DMARD10_REG_ACTR;
	buffer[1] = DMARD10_MODE_STANDBY;
	buffer[2] = DMARD10_MODE_OFF;

	return i2c_master_send(client, buffer, 3);
}