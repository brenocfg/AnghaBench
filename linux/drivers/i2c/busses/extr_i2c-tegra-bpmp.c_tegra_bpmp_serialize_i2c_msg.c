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
typedef  int u16 ;
struct tegra_bpmp_i2c {int dummy; } ;
struct TYPE_2__ {char* data_buf; unsigned int data_size; } ;
struct mrq_i2c_request {TYPE_1__ xfer; } ;
struct i2c_msg {int addr; int len; char* buf; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int SERIALI2C_RD ; 
 int tegra_bpmp_xlate_flags (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int tegra_bpmp_serialize_i2c_msg(struct tegra_bpmp_i2c *i2c,
					struct mrq_i2c_request *request,
					struct i2c_msg *msgs,
					unsigned int num)
{
	char *buf = request->xfer.data_buf;
	unsigned int i, j, pos = 0;
	int err;

	for (i = 0; i < num; i++) {
		struct i2c_msg *msg = &msgs[i];
		u16 flags = 0;

		err = tegra_bpmp_xlate_flags(msg->flags, &flags);
		if (err < 0)
			return err;

		buf[pos++] = msg->addr & 0xff;
		buf[pos++] = (msg->addr & 0xff00) >> 8;
		buf[pos++] = flags & 0xff;
		buf[pos++] = (flags & 0xff00) >> 8;
		buf[pos++] = msg->len & 0xff;
		buf[pos++] = (msg->len & 0xff00) >> 8;

		if ((flags & SERIALI2C_RD) == 0) {
			for (j = 0; j < msg->len; j++)
				buf[pos++] = msg->buf[j];
		}
	}

	request->xfer.data_size = pos;

	return 0;
}