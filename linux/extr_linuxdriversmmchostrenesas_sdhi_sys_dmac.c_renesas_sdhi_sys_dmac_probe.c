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
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  gen3_soc_whitelist ; 
 int /*<<< orphan*/ * of_device_get_match_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_rcar_gen3_compatible ; 
 int /*<<< orphan*/  of_rcar_r8a7795_compatible ; 
 int renesas_sdhi_probe (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  renesas_sdhi_sys_dmac_dma_ops ; 
 int /*<<< orphan*/  soc_device_match (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int renesas_sdhi_sys_dmac_probe(struct platform_device *pdev)
{
	if ((of_device_get_match_data(&pdev->dev) == &of_rcar_gen3_compatible ||
	    of_device_get_match_data(&pdev->dev) == &of_rcar_r8a7795_compatible) &&
	    !soc_device_match(gen3_soc_whitelist))
		return -ENODEV;

	return renesas_sdhi_probe(pdev, &renesas_sdhi_sys_dmac_dma_ops);
}