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
typedef  int /*<<< orphan*/  u32 ;
struct brcmf_sdio_dev {int /*<<< orphan*/  func1; } ;

/* Variables and functions */
 int /*<<< orphan*/  SBSDIO_SB_ACCESS_2_4B_FLAG ; 
 int /*<<< orphan*/  SBSDIO_SB_OFT_ADDR_MASK ; 
 int brcmf_sdiod_set_backplane_window (struct brcmf_sdio_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

u32 brcmf_sdiod_readl(struct brcmf_sdio_dev *sdiodev, u32 addr, int *ret)
{
	u32 data = 0;
	int retval;

	retval = brcmf_sdiod_set_backplane_window(sdiodev, addr);
	if (retval)
		goto out;

	addr &= SBSDIO_SB_OFT_ADDR_MASK;
	addr |= SBSDIO_SB_ACCESS_2_4B_FLAG;

	data = sdio_readl(sdiodev->func1, addr, &retval);

out:
	if (ret)
		*ret = retval;

	return data;
}