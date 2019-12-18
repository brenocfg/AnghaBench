#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  supplies; } ;
struct i2c_hid {TYPE_1__ pdata; scalar_t__ bufsize; struct hid_device* hid; } ;
struct i2c_client {int /*<<< orphan*/  irq; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct i2c_hid*) ; 
 int /*<<< orphan*/  hid_destroy_device (struct hid_device*) ; 
 struct i2c_hid* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_hid_free_buffers (struct i2c_hid*) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i2c_hid_remove(struct i2c_client *client)
{
	struct i2c_hid *ihid = i2c_get_clientdata(client);
	struct hid_device *hid;

	hid = ihid->hid;
	hid_destroy_device(hid);

	free_irq(client->irq, ihid);

	if (ihid->bufsize)
		i2c_hid_free_buffers(ihid);

	regulator_bulk_disable(ARRAY_SIZE(ihid->pdata.supplies),
			       ihid->pdata.supplies);

	return 0;
}