#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  (* power_off ) () ;} ;
struct kxtj9_data {TYPE_1__ pdata; TYPE_2__* client; int /*<<< orphan*/  ctrl_reg1; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_REG1 ; 
 int /*<<< orphan*/  PC1_OFF ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int i2c_smbus_write_byte_data (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void kxtj9_device_power_off(struct kxtj9_data *tj9)
{
	int err;

	tj9->ctrl_reg1 &= PC1_OFF;
	err = i2c_smbus_write_byte_data(tj9->client, CTRL_REG1, tj9->ctrl_reg1);
	if (err < 0)
		dev_err(&tj9->client->dev, "soft power off failed\n");

	if (tj9->pdata.power_off)
		tj9->pdata.power_off();
}