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
struct sii9234 {int /*<<< orphan*/  bridge; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_bridge_remove (int /*<<< orphan*/ *) ; 
 struct sii9234* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  sii9234_cable_out (struct sii9234*) ; 
 int /*<<< orphan*/  sii9234_deinit_resources (struct sii9234*) ; 

__attribute__((used)) static int sii9234_remove(struct i2c_client *client)
{
	struct sii9234 *ctx = i2c_get_clientdata(client);

	sii9234_cable_out(ctx);
	drm_bridge_remove(&ctx->bridge);
	sii9234_deinit_resources(ctx);

	return 0;
}