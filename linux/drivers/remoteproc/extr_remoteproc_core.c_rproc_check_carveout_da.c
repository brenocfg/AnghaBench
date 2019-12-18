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
typedef  scalar_t__ u32 ;
struct rproc_mem_entry {scalar_t__ len; scalar_t__ da; } ;
struct device {int dummy; } ;
struct rproc {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ FW_RSC_ADDR_ANY ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 

__attribute__((used)) static int rproc_check_carveout_da(struct rproc *rproc,
				   struct rproc_mem_entry *mem, u32 da, u32 len)
{
	struct device *dev = &rproc->dev;
	int delta;

	/* Check requested resource length */
	if (len > mem->len) {
		dev_err(dev, "Registered carveout doesn't fit len request\n");
		return -EINVAL;
	}

	if (da != FW_RSC_ADDR_ANY && mem->da == FW_RSC_ADDR_ANY) {
		/* Address doesn't match registered carveout configuration */
		return -EINVAL;
	} else if (da != FW_RSC_ADDR_ANY && mem->da != FW_RSC_ADDR_ANY) {
		delta = da - mem->da;

		/* Check requested resource belongs to registered carveout */
		if (delta < 0) {
			dev_err(dev,
				"Registered carveout doesn't fit da request\n");
			return -EINVAL;
		}

		if (delta + len > mem->len) {
			dev_err(dev,
				"Registered carveout doesn't fit len request\n");
			return -EINVAL;
		}
	}

	return 0;
}