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
typedef  int /*<<< orphan*/  u32 ;
struct firmware {int /*<<< orphan*/  data; } ;
struct brcmf_sdio {TYPE_1__* sdiodev; int /*<<< orphan*/  ci; } ;
struct TYPE_2__ {int /*<<< orphan*/  func1; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_AVAIL ; 
 int /*<<< orphan*/  CLK_SDONLY ; 
 int /*<<< orphan*/  SDIO ; 
 int /*<<< orphan*/  brcmf_chip_set_active (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_err (char*) ; 
 int /*<<< orphan*/  brcmf_fw_nvram_free (void*) ; 
 int /*<<< orphan*/  brcmf_sdio_clkctl (struct brcmf_sdio*,int /*<<< orphan*/ ,int) ; 
 int brcmf_sdio_download_code_file (struct brcmf_sdio*,struct firmware const*) ; 
 int brcmf_sdio_download_nvram (struct brcmf_sdio*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_unaligned_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int /*<<< orphan*/  sdio_claim_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_release_host (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int brcmf_sdio_download_firmware(struct brcmf_sdio *bus,
					const struct firmware *fw,
					void *nvram, u32 nvlen)
{
	int bcmerror;
	u32 rstvec;

	sdio_claim_host(bus->sdiodev->func1);
	brcmf_sdio_clkctl(bus, CLK_AVAIL, false);

	rstvec = get_unaligned_le32(fw->data);
	brcmf_dbg(SDIO, "firmware rstvec: %x\n", rstvec);

	bcmerror = brcmf_sdio_download_code_file(bus, fw);
	release_firmware(fw);
	if (bcmerror) {
		brcmf_err("dongle image file download failed\n");
		brcmf_fw_nvram_free(nvram);
		goto err;
	}

	bcmerror = brcmf_sdio_download_nvram(bus, nvram, nvlen);
	brcmf_fw_nvram_free(nvram);
	if (bcmerror) {
		brcmf_err("dongle nvram file download failed\n");
		goto err;
	}

	/* Take arm out of reset */
	if (!brcmf_chip_set_active(bus->ci, rstvec)) {
		brcmf_err("error getting out of ARM core reset\n");
		goto err;
	}

err:
	brcmf_sdio_clkctl(bus, CLK_SDONLY, false);
	sdio_release_host(bus->sdiodev->func1);
	return bcmerror;
}