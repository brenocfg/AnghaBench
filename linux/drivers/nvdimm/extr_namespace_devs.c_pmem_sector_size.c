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
struct nd_namespace_pmem {int lbasize; } ;
struct nd_namespace_common {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_WARN (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ is_namespace_pmem (int /*<<< orphan*/ *) ; 
 struct nd_namespace_pmem* to_nd_namespace_pmem (int /*<<< orphan*/ *) ; 

unsigned int pmem_sector_size(struct nd_namespace_common *ndns)
{
	if (is_namespace_pmem(&ndns->dev)) {
		struct nd_namespace_pmem *nspm;

		nspm = to_nd_namespace_pmem(&ndns->dev);
		if (nspm->lbasize == 0 || nspm->lbasize == 512)
			/* default */;
		else if (nspm->lbasize == 4096)
			return 4096;
		else
			dev_WARN(&ndns->dev, "unsupported sector size: %ld\n",
					nspm->lbasize);
	}

	/*
	 * There is no namespace label (is_namespace_io()), or the label
	 * indicates the default sector size.
	 */
	return 512;
}