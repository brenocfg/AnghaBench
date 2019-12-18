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
struct tc_data {int /*<<< orphan*/  aux; int /*<<< orphan*/  bridge; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_bridge_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_dp_aux_unregister (int /*<<< orphan*/ *) ; 
 struct tc_data* i2c_get_clientdata (struct i2c_client*) ; 

__attribute__((used)) static int tc_remove(struct i2c_client *client)
{
	struct tc_data *tc = i2c_get_clientdata(client);

	drm_bridge_remove(&tc->bridge);
	drm_dp_aux_unregister(&tc->aux);

	return 0;
}