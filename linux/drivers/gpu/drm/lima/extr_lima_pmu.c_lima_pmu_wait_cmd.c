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
struct lima_ip {scalar_t__ iomem; struct lima_device* dev; } ;
struct lima_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIMA_PMU_INT_CLEAR ; 
 int LIMA_PMU_INT_CMD_MASK ; 
 scalar_t__ LIMA_PMU_INT_RAWSTAT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pmu_write (int /*<<< orphan*/ ,int) ; 
 int readl_poll_timeout (scalar_t__,int,int,int,int) ; 

__attribute__((used)) static int lima_pmu_wait_cmd(struct lima_ip *ip)
{
	struct lima_device *dev = ip->dev;
	int err;
	u32 v;

	err = readl_poll_timeout(ip->iomem + LIMA_PMU_INT_RAWSTAT,
				 v, v & LIMA_PMU_INT_CMD_MASK,
				 100, 100000);
	if (err) {
		dev_err(dev->dev, "timeout wait pmd cmd\n");
		return err;
	}

	pmu_write(LIMA_PMU_INT_CLEAR, LIMA_PMU_INT_CMD_MASK);
	return 0;
}