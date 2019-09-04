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
struct adv7511 {scalar_t__ type; int /*<<< orphan*/  i2c_edid; int /*<<< orphan*/  i2c_packet; int /*<<< orphan*/  cec_adap; int /*<<< orphan*/  bridge; scalar_t__ cec_clk; int /*<<< orphan*/  i2c_cec; } ;

/* Variables and functions */
 scalar_t__ ADV7533 ; 
 int /*<<< orphan*/  adv7511_audio_exit (struct adv7511*) ; 
 int /*<<< orphan*/  adv7511_uninit_regulators (struct adv7511*) ; 
 int /*<<< orphan*/  adv7533_detach_dsi (struct adv7511*) ; 
 int /*<<< orphan*/  cec_unregister_adapter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int /*<<< orphan*/  drm_bridge_remove (int /*<<< orphan*/ *) ; 
 struct adv7511* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_unregister_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adv7511_remove(struct i2c_client *i2c)
{
	struct adv7511 *adv7511 = i2c_get_clientdata(i2c);

	if (adv7511->type == ADV7533)
		adv7533_detach_dsi(adv7511);
	i2c_unregister_device(adv7511->i2c_cec);
	if (adv7511->cec_clk)
		clk_disable_unprepare(adv7511->cec_clk);

	adv7511_uninit_regulators(adv7511);

	drm_bridge_remove(&adv7511->bridge);

	adv7511_audio_exit(adv7511);

	cec_unregister_adapter(adv7511->cec_adap);

	i2c_unregister_device(adv7511->i2c_packet);
	i2c_unregister_device(adv7511->i2c_edid);

	return 0;
}