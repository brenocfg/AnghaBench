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
typedef  int u32 ;
typedef  int u16 ;
struct ov13858 {int /*<<< orphan*/  sd; } ;
struct i2c_client {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int i2c_master_send (struct i2c_client*,int*,int) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ov13858_write_reg(struct ov13858 *ov13858, u16 reg, u32 len,
			     u32 __val)
{
	struct i2c_client *client = v4l2_get_subdevdata(&ov13858->sd);
	int buf_i, val_i;
	u8 buf[6], *val_p;
	__be32 val;

	if (len > 4)
		return -EINVAL;

	buf[0] = reg >> 8;
	buf[1] = reg & 0xff;

	val = cpu_to_be32(__val);
	val_p = (u8 *)&val;
	buf_i = 2;
	val_i = 4 - len;

	while (val_i < 4)
		buf[buf_i++] = val_p[val_i++];

	if (i2c_master_send(client, buf, len + 2) != len + 2)
		return -EIO;

	return 0;
}