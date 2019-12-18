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
typedef  int /*<<< orphan*/  u32 ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int p8_i2c_occ_putscom (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int p8_i2c_occ_putscom_u32(struct i2c_client *client, u32 address,
				  u32 data0, u32 data1)
{
	u8 buf[8];

	memcpy(buf, &data0, 4);
	memcpy(buf + 4, &data1, 4);

	return p8_i2c_occ_putscom(client, address, buf);
}