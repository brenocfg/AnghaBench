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
struct adv748x_state {int /*<<< orphan*/  mutex; int /*<<< orphan*/  txb; int /*<<< orphan*/  txa; int /*<<< orphan*/  hdmi; int /*<<< orphan*/  afe; } ;

/* Variables and functions */
 int /*<<< orphan*/  adv748x_afe_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  adv748x_csi2_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  adv748x_dt_cleanup (struct adv748x_state*) ; 
 int /*<<< orphan*/  adv748x_hdmi_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  adv748x_unregister_clients (struct adv748x_state*) ; 
 struct adv748x_state* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adv748x_remove(struct i2c_client *client)
{
	struct adv748x_state *state = i2c_get_clientdata(client);

	adv748x_afe_cleanup(&state->afe);
	adv748x_hdmi_cleanup(&state->hdmi);

	adv748x_csi2_cleanup(&state->txa);
	adv748x_csi2_cleanup(&state->txb);

	adv748x_unregister_clients(state);
	adv748x_dt_cleanup(state);
	mutex_destroy(&state->mutex);

	return 0;
}