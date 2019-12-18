#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct brcmf_sdio_dev {TYPE_2__* func2; int /*<<< orphan*/  bus; TYPE_2__* func1; } ;
struct TYPE_7__ {TYPE_1__* card; int /*<<< orphan*/  enable_timeout; } ;
struct TYPE_6__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  SDIO_FUNC1_BLOCKSIZE ; 
 int /*<<< orphan*/  SDIO_FUNC2_BLOCKSIZE ; 
 int /*<<< orphan*/  SDIO_WAIT_F2RDY ; 
 int /*<<< orphan*/  brcmf_err (char*,...) ; 
 int /*<<< orphan*/  brcmf_sdio_probe (struct brcmf_sdio_dev*) ; 
 int brcmf_sdiod_freezer_attach (struct brcmf_sdio_dev*) ; 
 int /*<<< orphan*/  brcmf_sdiod_host_fixup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_sdiod_remove (struct brcmf_sdio_dev*) ; 
 int /*<<< orphan*/  sdio_claim_host (TYPE_2__*) ; 
 int sdio_enable_func (TYPE_2__*) ; 
 int /*<<< orphan*/  sdio_release_host (TYPE_2__*) ; 
 int sdio_set_block_size (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int brcmf_sdiod_probe(struct brcmf_sdio_dev *sdiodev)
{
	int ret = 0;

	sdio_claim_host(sdiodev->func1);

	ret = sdio_set_block_size(sdiodev->func1, SDIO_FUNC1_BLOCKSIZE);
	if (ret) {
		brcmf_err("Failed to set F1 blocksize\n");
		sdio_release_host(sdiodev->func1);
		goto out;
	}
	ret = sdio_set_block_size(sdiodev->func2, SDIO_FUNC2_BLOCKSIZE);
	if (ret) {
		brcmf_err("Failed to set F2 blocksize\n");
		sdio_release_host(sdiodev->func1);
		goto out;
	}

	/* increase F2 timeout */
	sdiodev->func2->enable_timeout = SDIO_WAIT_F2RDY;

	/* Enable Function 1 */
	ret = sdio_enable_func(sdiodev->func1);
	sdio_release_host(sdiodev->func1);
	if (ret) {
		brcmf_err("Failed to enable F1: err=%d\n", ret);
		goto out;
	}

	ret = brcmf_sdiod_freezer_attach(sdiodev);
	if (ret)
		goto out;

	/* try to attach to the target device */
	sdiodev->bus = brcmf_sdio_probe(sdiodev);
	if (!sdiodev->bus) {
		ret = -ENODEV;
		goto out;
	}
	brcmf_sdiod_host_fixup(sdiodev->func2->card->host);
out:
	if (ret)
		brcmf_sdiod_remove(sdiodev);

	return ret;
}