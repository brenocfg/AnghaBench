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
typedef  int /*<<< orphan*/  uint32_t ;
struct fmc_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmc_readl (struct fmc_device*,unsigned long) ; 

__attribute__((used)) static uint32_t __sdb_rd(struct fmc_device *fmc, unsigned long address,
			int convert)
{
	uint32_t res = fmc_readl(fmc, address);
	if (convert)
		return __be32_to_cpu(res);
	return res;
}