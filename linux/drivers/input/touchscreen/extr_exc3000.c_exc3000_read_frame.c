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
typedef  scalar_t__ u8 ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int EXC3000_LEN_FRAME ; 
 scalar_t__ EXC3000_MT_EVENT ; 
 int get_unaligned_le16 (scalar_t__*) ; 
 int i2c_master_recv (struct i2c_client*,scalar_t__*,int) ; 
 int i2c_master_send (struct i2c_client*,char*,int) ; 

__attribute__((used)) static int exc3000_read_frame(struct i2c_client *client, u8 *buf)
{
	int ret;

	ret = i2c_master_send(client, "'", 2);
	if (ret < 0)
		return ret;

	if (ret != 2)
		return -EIO;

	ret = i2c_master_recv(client, buf, EXC3000_LEN_FRAME);
	if (ret < 0)
		return ret;

	if (ret != EXC3000_LEN_FRAME)
		return -EIO;

	if (get_unaligned_le16(buf) != EXC3000_LEN_FRAME ||
			buf[2] != EXC3000_MT_EVENT)
		return -EINVAL;

	return 0;
}