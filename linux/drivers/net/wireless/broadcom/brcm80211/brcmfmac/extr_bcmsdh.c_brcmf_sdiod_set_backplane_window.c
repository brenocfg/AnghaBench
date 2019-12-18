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
typedef  int u32 ;
struct brcmf_sdio_dev {int sbwad; } ;

/* Variables and functions */
 scalar_t__ SBSDIO_FUNC1_SBADDRLOW ; 
 int SBSDIO_SBWINDOW_MASK ; 
 int /*<<< orphan*/  brcmf_sdiod_writeb (struct brcmf_sdio_dev*,scalar_t__,int,int*) ; 

__attribute__((used)) static int brcmf_sdiod_set_backplane_window(struct brcmf_sdio_dev *sdiodev,
					    u32 addr)
{
	u32 v, bar0 = addr & SBSDIO_SBWINDOW_MASK;
	int err = 0, i;

	if (bar0 == sdiodev->sbwad)
		return 0;

	v = bar0 >> 8;

	for (i = 0 ; i < 3 && !err ; i++, v >>= 8)
		brcmf_sdiod_writeb(sdiodev, SBSDIO_FUNC1_SBADDRLOW + i,
				   v & 0xff, &err);

	if (!err)
		sdiodev->sbwad = bar0;

	return err;
}