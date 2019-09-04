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
struct tda9950_priv {int /*<<< orphan*/  notify; int /*<<< orphan*/  adap; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cec_notifier_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cec_unregister_adapter (int /*<<< orphan*/ ) ; 
 struct tda9950_priv* i2c_get_clientdata (struct i2c_client*) ; 

__attribute__((used)) static int tda9950_remove(struct i2c_client *client)
{
	struct tda9950_priv *priv = i2c_get_clientdata(client);

	cec_unregister_adapter(priv->adap);
	cec_notifier_put(priv->notify);

	return 0;
}