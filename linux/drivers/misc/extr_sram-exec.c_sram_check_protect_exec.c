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
struct sram_reserve {unsigned long size; } ;
struct sram_partition {scalar_t__ base; } ;
struct sram_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PAGE_ALIGNED (unsigned long) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

int sram_check_protect_exec(struct sram_dev *sram, struct sram_reserve *block,
			    struct sram_partition *part)
{
	unsigned long base = (unsigned long)part->base;
	unsigned long end = base + block->size;

	if (!PAGE_ALIGNED(base) || !PAGE_ALIGNED(end)) {
		dev_err(sram->dev,
			"SRAM pool marked with 'protect-exec' is not page aligned and will not be created.\n");
		return -ENOMEM;
	}

	return 0;
}