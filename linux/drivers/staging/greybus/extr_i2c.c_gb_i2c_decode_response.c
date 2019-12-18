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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct i2c_msg {int flags; int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct gb_i2c_transfer_response {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int I2C_M_RD ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gb_i2c_decode_response(struct i2c_msg *msgs, u32 msg_count,
				   struct gb_i2c_transfer_response *response)
{
	struct i2c_msg *msg = msgs;
	u8 *data;
	u32 i;

	if (!response)
		return;
	data = response->data;
	for (i = 0; i < msg_count; i++) {
		if (msg->flags & I2C_M_RD) {
			memcpy(msg->buf, data, msg->len);
			data += msg->len;
		}
		msg++;
	}
}