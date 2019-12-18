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
struct pi3usb30532 {int /*<<< orphan*/  sw; int /*<<< orphan*/  mux; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct pi3usb30532* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  typec_mux_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  typec_switch_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pi3usb30532_remove(struct i2c_client *client)
{
	struct pi3usb30532 *pi = i2c_get_clientdata(client);

	typec_mux_unregister(pi->mux);
	typec_switch_unregister(pi->sw);
	return 0;
}