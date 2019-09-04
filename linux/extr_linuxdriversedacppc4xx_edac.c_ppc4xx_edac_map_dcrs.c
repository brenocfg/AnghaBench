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
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  dcr_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  DCR_MAP_OK (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 unsigned int SDRAM_DCR_RESOURCE_LEN ; 
 int /*<<< orphan*/  dcr_map (struct device_node const*,unsigned int,unsigned int) ; 
 unsigned int dcr_resource_len (struct device_node const*,int /*<<< orphan*/ ) ; 
 unsigned int dcr_resource_start (struct device_node const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppc4xx_edac_printk (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int ppc4xx_edac_map_dcrs(const struct device_node *np,
				dcr_host_t *dcr_host)
{
	unsigned int dcr_base, dcr_len;

	if (np == NULL || dcr_host == NULL)
		return -EINVAL;

	/* Get the DCR resource extent and sanity check the values. */

	dcr_base = dcr_resource_start(np, 0);
	dcr_len = dcr_resource_len(np, 0);

	if (dcr_base == 0 || dcr_len == 0) {
		ppc4xx_edac_printk(KERN_ERR,
				   "Failed to obtain DCR property.\n");
		return -ENODEV;
	}

	if (dcr_len != SDRAM_DCR_RESOURCE_LEN) {
		ppc4xx_edac_printk(KERN_ERR,
				   "Unexpected DCR length %d, expected %d.\n",
				   dcr_len, SDRAM_DCR_RESOURCE_LEN);
		return -ENODEV;
	}

	/*  Attempt to map the DCR extent. */

	*dcr_host = dcr_map(np, dcr_base, dcr_len);

	if (!DCR_MAP_OK(*dcr_host)) {
		ppc4xx_edac_printk(KERN_INFO, "Failed to map DCRs.\n");
		    return -ENODEV;
	}

	return 0;
}