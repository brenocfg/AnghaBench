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
struct mmc_data {scalar_t__ host_cookie; int /*<<< orphan*/  sg_len; int /*<<< orphan*/  sg; } ;
struct dw_mci {int /*<<< orphan*/  dev; struct mmc_data* data; } ;

/* Variables and functions */
 scalar_t__ COOKIE_MAPPED ; 
 scalar_t__ COOKIE_UNMAPPED ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_get_dma_dir (struct mmc_data*) ; 

__attribute__((used)) static void dw_mci_dma_cleanup(struct dw_mci *host)
{
	struct mmc_data *data = host->data;

	if (data && data->host_cookie == COOKIE_MAPPED) {
		dma_unmap_sg(host->dev,
			     data->sg,
			     data->sg_len,
			     mmc_get_dma_dir(data));
		data->host_cookie = COOKIE_UNMAPPED;
	}
}