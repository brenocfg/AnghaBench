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
typedef  int u16 ;
struct watchdog_device {int /*<<< orphan*/  parent; } ;
struct i2c_client {int dummy; } ;
typedef  int /*<<< orphan*/  address ;

/* Variables and functions */
 int /*<<< orphan*/  ZIIRAVE_CMD_DOWNLOAD_SET_READ_ADDR ; 
 int i2c_smbus_write_block_data (struct i2c_client*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_unaligned_le16 (int const,int /*<<< orphan*/ *) ; 
 struct i2c_client* to_i2c_client (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ziirave_firm_set_read_addr(struct watchdog_device *wdd, u32 addr)
{
	struct i2c_client *client = to_i2c_client(wdd->parent);
	const u16 addr16 = (u16)addr / 2;
	u8 address[2];

	put_unaligned_le16(addr16, address);

	return i2c_smbus_write_block_data(client,
					  ZIIRAVE_CMD_DOWNLOAD_SET_READ_ADDR,
					  sizeof(address), address);
}