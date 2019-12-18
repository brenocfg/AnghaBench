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
struct vub300_mmc_host {TYPE_1__* udev; } ;
struct mmc_host {int dummy; } ;
struct mmc_card {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 struct vub300_mmc_host* mmc_priv (struct mmc_host*) ; 

__attribute__((used)) static void vub300_init_card(struct mmc_host *mmc, struct mmc_card *card)
{				/* NOT irq */
	struct vub300_mmc_host *vub300 = mmc_priv(mmc);
	dev_info(&vub300->udev->dev, "NO host QUIRKS for this card\n");
}