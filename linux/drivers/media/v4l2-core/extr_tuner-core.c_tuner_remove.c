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
struct TYPE_2__ {int /*<<< orphan*/ * analog_demod_priv; } ;
struct tuner {int /*<<< orphan*/  list; TYPE_1__ fe; int /*<<< orphan*/  sd; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  kfree (struct tuner*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct tuner* to_tuner (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tuner_detach (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_device_unregister_subdev (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tuner_remove(struct i2c_client *client)
{
	struct tuner *t = to_tuner(i2c_get_clientdata(client));

	v4l2_device_unregister_subdev(&t->sd);
	tuner_detach(&t->fe);
	t->fe.analog_demod_priv = NULL;

	list_del(&t->list);
	kfree(t);
	return 0;
}