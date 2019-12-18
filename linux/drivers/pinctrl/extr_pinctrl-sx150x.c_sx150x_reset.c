#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sx150x_pinctrl {TYPE_3__* data; int /*<<< orphan*/  client; } ;
struct TYPE_4__ {int /*<<< orphan*/  reg_reset; } ;
struct TYPE_5__ {TYPE_1__ x789; } ;
struct TYPE_6__ {TYPE_2__ pri; } ;

/* Variables and functions */
 int /*<<< orphan*/  SX150X_789_RESET_KEY1 ; 
 int /*<<< orphan*/  SX150X_789_RESET_KEY2 ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sx150x_reset(struct sx150x_pinctrl *pctl)
{
	int err;

	err = i2c_smbus_write_byte_data(pctl->client,
					pctl->data->pri.x789.reg_reset,
					SX150X_789_RESET_KEY1);
	if (err < 0)
		return err;

	err = i2c_smbus_write_byte_data(pctl->client,
					pctl->data->pri.x789.reg_reset,
					SX150X_789_RESET_KEY2);
	return err;
}