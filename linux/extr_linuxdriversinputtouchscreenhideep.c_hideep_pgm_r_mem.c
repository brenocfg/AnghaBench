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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {size_t len; int /*<<< orphan*/  addr; } ;
struct pgm_packet {TYPE_1__ header; } ;
struct i2c_msg {int len; size_t* buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct hideep_ts {TYPE_2__* client; scalar_t__ xfer_buf; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_4__ {int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct i2c_msg*) ; 
 int EINVAL ; 
 int EIO ; 
 size_t HIDEEP_NVM_PAGE_SIZE ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 

__attribute__((used)) static int hideep_pgm_r_mem(struct hideep_ts *ts, u32 addr,
			    __be32 *data, size_t count)
{
	struct pgm_packet *packet = (void *)ts->xfer_buf;
	size_t len = count * sizeof(*data);
	struct i2c_msg msg[] = {
		{
			.addr	= ts->client->addr,
			.len	= sizeof(packet->header.len) +
					sizeof(packet->header.addr),
			.buf	= &packet->header.len,
		},
		{
			.addr	= ts->client->addr,
			.flags	= I2C_M_RD,
			.len	= len,
			.buf	= (u8 *)data,
		},
	};
	int ret;

	if (len > HIDEEP_NVM_PAGE_SIZE)
		return -EINVAL;

	packet->header.len = count - 1;
	packet->header.addr = cpu_to_be32(addr);

	ret = i2c_transfer(ts->client->adapter, msg, ARRAY_SIZE(msg));
	if (ret != ARRAY_SIZE(msg))
		return ret < 0 ? ret : -EIO;

	return 0;
}