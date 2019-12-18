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
struct brcmf_pciedev_info {int dummy; } ;
struct brcmf_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  brcmf_pcie_write_tcm32 (struct brcmf_pciedev_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void brcmf_pcie_buscore_activate(void *ctx, struct brcmf_chip *chip,
					u32 rstvec)
{
	struct brcmf_pciedev_info *devinfo = (struct brcmf_pciedev_info *)ctx;

	brcmf_pcie_write_tcm32(devinfo, 0, rstvec);
}