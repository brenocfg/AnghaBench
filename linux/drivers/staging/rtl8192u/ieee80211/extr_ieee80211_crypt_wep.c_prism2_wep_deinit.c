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
struct prism2_wep_data {int /*<<< orphan*/  rx_tfm; int /*<<< orphan*/  tx_tfm; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_free_sync_skcipher (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void*) ; 

__attribute__((used)) static void prism2_wep_deinit(void *priv)
{
	struct prism2_wep_data *_priv = priv;

	if (_priv) {
		crypto_free_sync_skcipher(_priv->tx_tfm);
		crypto_free_sync_skcipher(_priv->rx_tfm);
	}
	kfree(priv);
}