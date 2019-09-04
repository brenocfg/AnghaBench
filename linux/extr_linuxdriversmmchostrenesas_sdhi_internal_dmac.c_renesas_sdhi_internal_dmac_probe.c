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
struct soc_device_attribute {scalar_t__ data; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  gen3_soc_whitelist ; 
 unsigned long global_flags ; 
 int /*<<< orphan*/  renesas_sdhi_internal_dmac_dma_ops ; 
 int renesas_sdhi_probe (struct platform_device*,int /*<<< orphan*/ *) ; 
 struct soc_device_attribute* soc_device_match (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int renesas_sdhi_internal_dmac_probe(struct platform_device *pdev)
{
	const struct soc_device_attribute *soc = soc_device_match(gen3_soc_whitelist);

	if (!soc)
		return -ENODEV;

	global_flags |= (unsigned long)soc->data;

	return renesas_sdhi_probe(pdev, &renesas_sdhi_internal_dmac_dma_ops);
}