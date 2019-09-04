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
typedef  int /*<<< orphan*/  val ;
typedef  int /*<<< orphan*/  uint8_t ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int dummy; } ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int /*<<< orphan*/  CH7006_VERSION_ID ; 
 int ENODEV ; 
 int /*<<< orphan*/  ch7006_dbg (struct i2c_client*,char*) ; 
 int /*<<< orphan*/  ch7006_err (struct i2c_client*,char*,int) ; 
 int /*<<< orphan*/  ch7006_info (struct i2c_client*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ch7006_write (struct i2c_client*,int,int) ; 
 int i2c_master_recv (struct i2c_client*,int /*<<< orphan*/ *,int) ; 
 int i2c_master_send (struct i2c_client*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ch7006_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	uint8_t addr = CH7006_VERSION_ID;
	uint8_t val;
	int ret;

	ch7006_dbg(client, "\n");

	ret = i2c_master_send(client, &addr, sizeof(addr));
	if (ret < 0)
		goto fail;

	ret = i2c_master_recv(client, &val, sizeof(val));
	if (ret < 0)
		goto fail;

	ch7006_info(client, "Detected version ID: %x\n", val);

	/* I don't know what this is for, but otherwise I get no
	 * signal.
	 */
	ch7006_write(client, 0x3d, 0x0);

	return 0;

fail:
	ch7006_err(client, "Error %d reading version ID\n", ret);

	return -ENODEV;
}