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
struct thermostat {int /*<<< orphan*/  clt; } ;

/* Variables and functions */
 int ENODEV ; 
 int i2c_master_recv (int /*<<< orphan*/ ,char*,int) ; 
 int i2c_master_send (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int
read_reg(struct thermostat* th, int reg)
{
	u8 reg_addr, data;
	int rc;

	reg_addr = (u8)reg;
	rc = i2c_master_send(th->clt, &reg_addr, 1);
	if (rc < 0)
		return rc;
	if (rc != 1)
		return -ENODEV;
	rc = i2c_master_recv(th->clt, (char *)&data, 1);
	if (rc < 0)
		return rc;
	return data;
}