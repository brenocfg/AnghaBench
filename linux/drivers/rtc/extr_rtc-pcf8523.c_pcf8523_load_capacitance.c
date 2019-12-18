#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct i2c_client {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_CONTROL1 ; 
 int /*<<< orphan*/  REG_CONTROL1_CAP_SEL ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 
 int pcf8523_read (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int pcf8523_write (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcf8523_load_capacitance(struct i2c_client *client)
{
	u32 load;
	u8 value;
	int err;

	err = pcf8523_read(client, REG_CONTROL1, &value);
	if (err < 0)
		return err;

	load = 12500;
	of_property_read_u32(client->dev.of_node, "quartz-load-femtofarads",
			     &load);

	switch (load) {
	default:
		dev_warn(&client->dev, "Unknown quartz-load-femtofarads value: %d. Assuming 12500",
			 load);
		/* fall through */
	case 12500:
		value |= REG_CONTROL1_CAP_SEL;
		break;
	case 7000:
		value &= ~REG_CONTROL1_CAP_SEL;
		break;
	}

	err = pcf8523_write(client, REG_CONTROL1, value);

	return err;
}