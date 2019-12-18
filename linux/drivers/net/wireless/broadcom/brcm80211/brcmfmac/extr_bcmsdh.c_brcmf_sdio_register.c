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

/* Variables and functions */
 int /*<<< orphan*/  brcmf_err (char*,int) ; 
 int /*<<< orphan*/  brcmf_sdmmc_driver ; 
 int sdio_register_driver (int /*<<< orphan*/ *) ; 

void brcmf_sdio_register(void)
{
	int ret;

	ret = sdio_register_driver(&brcmf_sdmmc_driver);
	if (ret)
		brcmf_err("sdio_register_driver failed: %d\n", ret);
}