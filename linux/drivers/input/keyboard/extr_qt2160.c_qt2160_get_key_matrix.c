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
typedef  int u16 ;
struct qt2160_data {int key_matrix; int /*<<< orphan*/ * keycodes; struct input_dev* input; struct i2c_client* client; } ;
struct input_dev {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  QT2160_CMD_GSTAT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int qt2160_read_block (struct i2c_client*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int qt2160_get_key_matrix(struct qt2160_data *qt2160)
{
	struct i2c_client *client = qt2160->client;
	struct input_dev *input = qt2160->input;
	u8 regs[6];
	u16 old_matrix, new_matrix;
	int ret, i, mask;

	dev_dbg(&client->dev, "requesting keys...\n");

	/*
	 * Read all registers from General Status Register
	 * to GPIOs register
	 */
	ret = qt2160_read_block(client, QT2160_CMD_GSTAT, regs, 6);
	if (ret) {
		dev_err(&client->dev,
			"could not perform chip read.\n");
		return ret;
	}

	old_matrix = qt2160->key_matrix;
	qt2160->key_matrix = new_matrix = (regs[2] << 8) | regs[1];

	mask = 0x01;
	for (i = 0; i < 16; ++i, mask <<= 1) {
		int keyval = new_matrix & mask;

		if ((old_matrix & mask) != keyval) {
			input_report_key(input, qt2160->keycodes[i], keyval);
			dev_dbg(&client->dev, "key %d %s\n",
				i, keyval ? "pressed" : "released");
		}
	}

	input_sync(input);

	return 0;
}