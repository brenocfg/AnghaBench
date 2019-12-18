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
struct i2c_client {int dummy; } ;
struct anx78xx {int /*<<< orphan*/  edid; int /*<<< orphan*/  bridge; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_bridge_remove (int /*<<< orphan*/ *) ; 
 struct anx78xx* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_i2c_dummy_clients (struct anx78xx*) ; 

__attribute__((used)) static int anx78xx_i2c_remove(struct i2c_client *client)
{
	struct anx78xx *anx78xx = i2c_get_clientdata(client);

	drm_bridge_remove(&anx78xx->bridge);

	unregister_i2c_dummy_clients(anx78xx);

	kfree(anx78xx->edid);

	return 0;
}