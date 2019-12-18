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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int i2c_master_send (struct i2c_client*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int saa7706h_i2c_send(struct i2c_client *client, const u8 *data, int len)
{
	int err = i2c_master_send(client, data, len);
	if (err == len)
		return 0;
	return err > 0 ? -EIO : err;
}