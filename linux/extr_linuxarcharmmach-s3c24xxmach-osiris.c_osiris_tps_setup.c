#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_5__ {TYPE_1__ dev; } ;

/* Variables and functions */
 TYPE_2__ osiris_tps_device ; 
 int platform_device_register (TYPE_2__*) ; 

__attribute__((used)) static int osiris_tps_setup(struct i2c_client *client, void *context)
{
	osiris_tps_device.dev.parent = &client->dev;
	return platform_device_register(&osiris_tps_device);
}