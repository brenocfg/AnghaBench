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
struct sh_mobile_i2c_data {int pos; TYPE_1__* msg; } ;
struct TYPE_2__ {unsigned char* buf; } ;

/* Variables and functions */
 unsigned char i2c_8bit_addr_from_msg (TYPE_1__*) ; 

__attribute__((used)) static void sh_mobile_i2c_get_data(struct sh_mobile_i2c_data *pd,
				   unsigned char *buf)
{
	switch (pd->pos) {
	case -1:
		*buf = i2c_8bit_addr_from_msg(pd->msg);
		break;
	default:
		*buf = pd->msg->buf[pd->pos];
	}
}