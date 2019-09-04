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
struct i2c_device_id {int dummy; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  SIL164_DEVICE_HI ; 
 int /*<<< orphan*/  SIL164_DEVICE_LO ; 
 int /*<<< orphan*/  SIL164_REVISION ; 
 int /*<<< orphan*/  SIL164_VENDOR_HI ; 
 int /*<<< orphan*/  SIL164_VENDOR_LO ; 
 int /*<<< orphan*/  sil164_dbg (struct i2c_client*,char*,int,int,int) ; 
 int /*<<< orphan*/  sil164_info (struct i2c_client*,char*,int,int,int) ; 
 int sil164_read (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sil164_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	int vendor = sil164_read(client, SIL164_VENDOR_HI) << 8 |
		sil164_read(client, SIL164_VENDOR_LO);
	int device = sil164_read(client, SIL164_DEVICE_HI) << 8 |
		sil164_read(client, SIL164_DEVICE_LO);
	int rev = sil164_read(client, SIL164_REVISION);

	if (vendor != 0x1 || device != 0x6) {
		sil164_dbg(client, "Unknown device %x:%x.%x\n",
			   vendor, device, rev);
		return -ENODEV;
	}

	sil164_info(client, "Detected device %x:%x.%x\n",
		    vendor, device, rev);

	return 0;
}