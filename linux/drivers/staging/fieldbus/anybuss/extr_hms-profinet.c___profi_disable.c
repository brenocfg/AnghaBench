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
struct profi_priv {int power_on; struct anybuss_client* client; } ;
struct anybuss_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  anybuss_set_power (struct anybuss_client*,int) ; 

__attribute__((used)) static int __profi_disable(struct profi_priv *priv)
{
	struct anybuss_client *client = priv->client;

	anybuss_set_power(client, false);
	priv->power_on = false;
	return 0;
}