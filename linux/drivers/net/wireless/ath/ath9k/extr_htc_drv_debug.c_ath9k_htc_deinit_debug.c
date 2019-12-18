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
struct ath9k_htc_priv {int /*<<< orphan*/  spec_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath9k_cmn_spectral_deinit_debug (int /*<<< orphan*/ *) ; 

void ath9k_htc_deinit_debug(struct ath9k_htc_priv *priv)
{
	ath9k_cmn_spectral_deinit_debug(&priv->spec_priv);
}