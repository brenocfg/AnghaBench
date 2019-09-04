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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int len; int /*<<< orphan*/  addr; } ;
struct pgm_packet {int /*<<< orphan*/  payload; TYPE_1__ header; } ;
struct i2c_msg {int* buf; int /*<<< orphan*/  len; int /*<<< orphan*/  addr; } ;
struct hideep_ts {TYPE_2__* client; scalar_t__ xfer_buf; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_4__ {int /*<<< orphan*/  adapter; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 size_t HIDEEP_NVM_PAGE_SIZE ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static int hideep_pgm_w_mem(struct hideep_ts *ts, u32 addr,
			    const __be32 *data, size_t count)
{
	struct pgm_packet *packet = (void *)ts->xfer_buf;
	size_t len = count * sizeof(*data);
	struct i2c_msg msg = {
		.addr	= ts->client->addr,
		.len	= len + sizeof(packet->header.len) +
				sizeof(packet->header.addr),
		.buf	= &packet->header.len,
	};
	int ret;

	if (len > HIDEEP_NVM_PAGE_SIZE)
		return -EINVAL;

	packet->header.len = 0x80 | (count - 1);
	packet->header.addr = cpu_to_be32(addr);
	memcpy(packet->payload, data, len);

	ret = i2c_transfer(ts->client->adapter, &msg, 1);
	if (ret != 1)
		return ret < 0 ? ret : -EIO;

	return 0;
}