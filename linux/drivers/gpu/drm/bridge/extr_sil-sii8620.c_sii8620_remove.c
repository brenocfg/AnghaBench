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
struct sii8620 {scalar_t__ cable_state; int /*<<< orphan*/  bridge; int /*<<< orphan*/  extcon_wq; int /*<<< orphan*/  extcon_nb; scalar_t__ extcon; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXTCON_DISP_MHL ; 
 int /*<<< orphan*/  drm_bridge_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extcon_unregister_notifier (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 struct sii8620* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  sii8620_cable_out (struct sii8620*) ; 

__attribute__((used)) static int sii8620_remove(struct i2c_client *client)
{
	struct sii8620 *ctx = i2c_get_clientdata(client);

	if (ctx->extcon) {
		extcon_unregister_notifier(ctx->extcon, EXTCON_DISP_MHL,
					   &ctx->extcon_nb);
		flush_work(&ctx->extcon_wq);
		if (ctx->cable_state > 0)
			sii8620_cable_out(ctx);
	} else {
		sii8620_cable_out(ctx);
	}
	drm_bridge_remove(&ctx->bridge);

	return 0;
}