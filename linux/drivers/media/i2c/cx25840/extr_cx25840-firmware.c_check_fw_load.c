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
 int EINVAL ; 
 int cx25840_read (struct i2c_client*,int) ; 
 int /*<<< orphan*/  get_fw_name (struct i2c_client*) ; 
 int /*<<< orphan*/  v4l_err (struct i2c_client*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l_info (struct i2c_client*,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int check_fw_load(struct i2c_client *client, int size)
{
	/* DL_ADDR_HB DL_ADDR_LB */
	int s = cx25840_read(client, 0x801) << 8;
	s |= cx25840_read(client, 0x800);

	if (size != s) {
		v4l_err(client, "firmware %s load failed\n",
				get_fw_name(client));
		return -EINVAL;
	}

	v4l_info(client, "loaded %s firmware (%d bytes)\n",
			get_fw_name(client), size);
	return 0;
}