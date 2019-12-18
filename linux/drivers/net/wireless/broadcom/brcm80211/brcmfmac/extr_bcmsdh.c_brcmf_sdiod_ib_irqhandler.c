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
struct sdio_func {int /*<<< orphan*/  dev; } ;
struct brcmf_sdio_dev {int /*<<< orphan*/  bus; } ;
struct TYPE_2__ {struct brcmf_sdio_dev* sdio; } ;
struct brcmf_bus {TYPE_1__ bus_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTR ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  brcmf_sdio_isr (int /*<<< orphan*/ ) ; 
 struct brcmf_bus* dev_get_drvdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void brcmf_sdiod_ib_irqhandler(struct sdio_func *func)
{
	struct brcmf_bus *bus_if = dev_get_drvdata(&func->dev);
	struct brcmf_sdio_dev *sdiodev = bus_if->bus_priv.sdio;

	brcmf_dbg(INTR, "IB intr triggered\n");

	brcmf_sdio_isr(sdiodev->bus);
}