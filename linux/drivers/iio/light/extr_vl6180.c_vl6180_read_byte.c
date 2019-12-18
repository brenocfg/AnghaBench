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
typedef  int /*<<< orphan*/  u16 ;
struct i2c_client {int dummy; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int vl6180_read (struct i2c_client*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int vl6180_read_byte(struct i2c_client *client, u16 cmd)
{
	u8 data;
	int ret;

	ret = vl6180_read(client, cmd, &data, sizeof(data));
	if (ret < 0)
		return ret;

	return data;
}