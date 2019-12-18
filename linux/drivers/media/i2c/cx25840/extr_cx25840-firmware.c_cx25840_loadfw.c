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
typedef  int /*<<< orphan*/  u32 ;
struct i2c_client {int dummy; } ;
struct firmware {int size; int* data; } ;
struct cx25840_state {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FWDEV (struct i2c_client*) ; 
 int FWSEND ; 
 int check_fw_load (struct i2c_client*,int) ; 
 int /*<<< orphan*/  cx25840_read (struct i2c_client*,int) ; 
 int /*<<< orphan*/  cx25840_write (struct i2c_client*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_fw_load (struct i2c_client*) ; 
 int fw_write (struct i2c_client*,int*,int) ; 
 char* get_fw_name (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_get_clientdata (struct i2c_client*) ; 
 scalar_t__ is_cx231xx (struct cx25840_state*) ; 
 scalar_t__ is_cx2388x (struct cx25840_state*) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 scalar_t__ request_firmware (struct firmware const**,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_fw_load (struct i2c_client*) ; 
 struct cx25840_state* to_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l_err (struct i2c_client*,char*,char const*) ; 

int cx25840_loadfw(struct i2c_client *client)
{
	struct cx25840_state *state = to_state(i2c_get_clientdata(client));
	const struct firmware *fw = NULL;
	u8 buffer[FWSEND];
	const u8 *ptr;
	const char *fwname = get_fw_name(client);
	int size, retval;
	int max_buf_size = FWSEND;
	u32 gpio_oe = 0, gpio_da = 0;

	if (is_cx2388x(state)) {
		/* Preserve the GPIO OE and output bits */
		gpio_oe = cx25840_read(client, 0x160);
		gpio_da = cx25840_read(client, 0x164);
	}

	/* cx231xx cannot accept more than 16 bytes at a time */
	if (is_cx231xx(state) && max_buf_size > 16)
		max_buf_size = 16;

	if (request_firmware(&fw, fwname, FWDEV(client)) != 0) {
		v4l_err(client, "unable to open firmware %s\n", fwname);
		return -EINVAL;
	}

	start_fw_load(client);

	buffer[0] = 0x08;
	buffer[1] = 0x02;

	size = fw->size;
	ptr = fw->data;
	while (size > 0) {
		int len = min(max_buf_size - 2, size);

		memcpy(buffer + 2, ptr, len);

		retval = fw_write(client, buffer, len + 2);

		if (retval < 0) {
			release_firmware(fw);
			return retval;
		}

		size -= len;
		ptr += len;
	}

	end_fw_load(client);

	size = fw->size;
	release_firmware(fw);

	if (is_cx2388x(state)) {
		/* Restore GPIO configuration after f/w load */
		cx25840_write(client, 0x160, gpio_oe);
		cx25840_write(client, 0x164, gpio_da);
	}

	return check_fw_load(client, size);
}