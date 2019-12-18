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
struct megasas_instance {TYPE_1__* pdev; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned long long,unsigned long long) ; 
 scalar_t__ upper_32_bits (scalar_t__) ; 

__attribute__((used)) static inline bool megasas_check_same_4gb_region
	(struct megasas_instance *instance, dma_addr_t start_addr, size_t size)
{
	dma_addr_t end_addr;

	end_addr = start_addr + size;

	if (upper_32_bits(start_addr) != upper_32_bits(end_addr)) {
		dev_err(&instance->pdev->dev,
			"Failed to get same 4GB boundary: start_addr: 0x%llx end_addr: 0x%llx\n",
			(unsigned long long)start_addr,
			(unsigned long long)end_addr);
		return false;
	}

	return true;
}