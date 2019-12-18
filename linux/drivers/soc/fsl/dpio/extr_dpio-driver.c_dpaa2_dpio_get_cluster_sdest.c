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
struct fsl_mc_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ls1088a_soc ; 
 int /*<<< orphan*/  ls2080a_soc ; 
 int /*<<< orphan*/  ls2088a_soc ; 
 int /*<<< orphan*/  lx2160a_soc ; 
 scalar_t__ soc_device_match (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dpaa2_dpio_get_cluster_sdest(struct fsl_mc_device *dpio_dev, int cpu)
{
	int cluster_base, cluster_size;

	if (soc_device_match(ls1088a_soc)) {
		cluster_base = 2;
		cluster_size = 4;
	} else if (soc_device_match(ls2080a_soc) ||
		   soc_device_match(ls2088a_soc) ||
		   soc_device_match(lx2160a_soc)) {
		cluster_base = 0;
		cluster_size = 2;
	} else {
		dev_err(&dpio_dev->dev, "unknown SoC version\n");
		return -1;
	}

	return cluster_base + cpu / cluster_size;
}