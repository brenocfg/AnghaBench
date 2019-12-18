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
typedef  int u32 ;
struct i2c_client {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int EIO ; 
 int i2c_master_send (struct i2c_client*,char const*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int p8_i2c_occ_putscom(struct i2c_client *client, u32 address, u8 *data)
{
	u32 buf[3];
	ssize_t rc;

	/* p8 i2c slave requires shift */
	address <<= 1;

	/* address is bus-endian; data passed through from user as-is */
	buf[0] = address;
	memcpy(&buf[1], &data[4], sizeof(u32));
	memcpy(&buf[2], data, sizeof(u32));

	rc = i2c_master_send(client, (const char *)buf, sizeof(buf));
	if (rc < 0)
		return rc;
	else if (rc != sizeof(buf))
		return -EIO;

	return 0;
}