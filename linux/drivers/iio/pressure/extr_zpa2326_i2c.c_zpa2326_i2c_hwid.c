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
struct i2c_client {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 unsigned int ZPA2326_DEVICE_ID ; 
 unsigned int ZPA2326_DEVICE_ID_SA0_SHIFT ; 
 unsigned int ZPA2326_SA0 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int zpa2326_i2c_hwid(const struct i2c_client *client)
{
#define ZPA2326_SA0(_addr)          (_addr & BIT(0))
#define ZPA2326_DEVICE_ID_SA0_SHIFT (1)

	/* Identification register bit 1 mirrors device address bit 0. */
	return (ZPA2326_DEVICE_ID |
		(ZPA2326_SA0(client->addr) << ZPA2326_DEVICE_ID_SA0_SHIFT));
}