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
struct s3c24xx_i2c {int msg_ptr; TYPE_1__* msg; } ;
struct TYPE_2__ {int flags; int len; } ;

/* Variables and functions */
 int I2C_M_RECV_LEN ; 

__attribute__((used)) static inline int is_msglast(struct s3c24xx_i2c *i2c)
{
	/*
	 * msg->len is always 1 for the first byte of smbus block read.
	 * Actual length will be read from slave. More bytes will be
	 * read according to the length then.
	 */
	if (i2c->msg->flags & I2C_M_RECV_LEN && i2c->msg->len == 1)
		return 0;

	return i2c->msg_ptr == i2c->msg->len-1;
}