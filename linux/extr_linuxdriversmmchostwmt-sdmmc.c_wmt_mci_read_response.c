#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct wmt_mci_priv {TYPE_1__* cmd; scalar_t__ sdmmc_base; } ;
struct mmc_host {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * resp; } ;

/* Variables and functions */
 scalar_t__ SDMMC_RSP ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 struct wmt_mci_priv* mmc_priv (struct mmc_host*) ; 
 int readb (scalar_t__) ; 

__attribute__((used)) static void wmt_mci_read_response(struct mmc_host *mmc)
{
	struct wmt_mci_priv *priv;
	int idx1, idx2;
	u8 tmp_resp;
	u32 response;

	priv = mmc_priv(mmc);

	for (idx1 = 0; idx1 < 4; idx1++) {
		response = 0;
		for (idx2 = 0; idx2 < 4; idx2++) {
			if ((idx1 == 3) && (idx2 == 3))
				tmp_resp = readb(priv->sdmmc_base + SDMMC_RSP);
			else
				tmp_resp = readb(priv->sdmmc_base + SDMMC_RSP +
						 (idx1*4) + idx2 + 1);
			response |= (tmp_resp << (idx2 * 8));
		}
		priv->cmd->resp[idx1] = cpu_to_be32(response);
	}
}