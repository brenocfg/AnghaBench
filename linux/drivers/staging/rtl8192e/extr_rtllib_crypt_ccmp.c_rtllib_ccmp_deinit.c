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
struct rtllib_ccmp_data {scalar_t__ tfm; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_free_aead (scalar_t__) ; 
 int /*<<< orphan*/  kfree (void*) ; 

__attribute__((used)) static void rtllib_ccmp_deinit(void *priv)
{
	struct rtllib_ccmp_data *_priv = priv;

	if (_priv && _priv->tfm)
		crypto_free_aead(_priv->tfm);
	kfree(priv);
}