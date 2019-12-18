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
struct iwl_rxon_cmd {int /*<<< orphan*/  filter_flags; } ;
struct iwl_rxon_context {struct iwl_rxon_cmd staging; } ;
struct iwl_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RXON_FILTER_DIS_DECRYPT_MSK ; 

__attribute__((used)) static void iwl_set_rxon_hwcrypto(struct iwl_priv *priv,
				  struct iwl_rxon_context *ctx, int hw_decrypt)
{
	struct iwl_rxon_cmd *rxon = &ctx->staging;

	if (hw_decrypt)
		rxon->filter_flags &= ~RXON_FILTER_DIS_DECRYPT_MSK;
	else
		rxon->filter_flags |= RXON_FILTER_DIS_DECRYPT_MSK;

}