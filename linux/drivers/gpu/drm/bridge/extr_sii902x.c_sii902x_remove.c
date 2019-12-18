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
struct sii902x {int /*<<< orphan*/  bridge; int /*<<< orphan*/  i2cmux; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_bridge_remove (int /*<<< orphan*/ *) ; 
 struct sii902x* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_mux_del_adapters (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sii902x_remove(struct i2c_client *client)

{
	struct sii902x *sii902x = i2c_get_clientdata(client);

	i2c_mux_del_adapters(sii902x->i2cmux);
	drm_bridge_remove(&sii902x->bridge);

	return 0;
}