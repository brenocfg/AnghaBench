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
struct ptn3460_bridge {int /*<<< orphan*/  bridge; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_bridge_remove (int /*<<< orphan*/ *) ; 
 struct ptn3460_bridge* i2c_get_clientdata (struct i2c_client*) ; 

__attribute__((used)) static int ptn3460_remove(struct i2c_client *client)
{
	struct ptn3460_bridge *ptn_bridge = i2c_get_clientdata(client);

	drm_bridge_remove(&ptn_bridge->bridge);

	return 0;
}