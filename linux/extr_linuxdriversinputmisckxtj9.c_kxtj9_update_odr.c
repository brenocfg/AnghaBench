#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct kxtj9_data {int /*<<< orphan*/  ctrl_reg1; int /*<<< orphan*/  client; int /*<<< orphan*/  data_ctrl; } ;
struct TYPE_3__ {unsigned int cutoff; int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  CTRL_REG1 ; 
 int /*<<< orphan*/  DATA_CTRL ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* kxtj9_odr_table ; 

__attribute__((used)) static int kxtj9_update_odr(struct kxtj9_data *tj9, unsigned int poll_interval)
{
	int err;
	int i;

	/* Use the lowest ODR that can support the requested poll interval */
	for (i = 0; i < ARRAY_SIZE(kxtj9_odr_table); i++) {
		tj9->data_ctrl = kxtj9_odr_table[i].mask;
		if (poll_interval < kxtj9_odr_table[i].cutoff)
			break;
	}

	err = i2c_smbus_write_byte_data(tj9->client, CTRL_REG1, 0);
	if (err < 0)
		return err;

	err = i2c_smbus_write_byte_data(tj9->client, DATA_CTRL, tj9->data_ctrl);
	if (err < 0)
		return err;

	err = i2c_smbus_write_byte_data(tj9->client, CTRL_REG1, tj9->ctrl_reg1);
	if (err < 0)
		return err;

	return 0;
}