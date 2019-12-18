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
struct mwifiex_private {int dummy; } ;
struct mwifiex_adapter {int priv_num; struct mwifiex_private** priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  mwifiex_deauthenticate (struct mwifiex_private*,int /*<<< orphan*/ *) ; 

void mwifiex_deauthenticate_all(struct mwifiex_adapter *adapter)
{
	struct mwifiex_private *priv;
	int i;

	for (i = 0; i < adapter->priv_num; i++) {
		priv = adapter->priv[i];
		if (priv)
			mwifiex_deauthenticate(priv, NULL);
	}
}