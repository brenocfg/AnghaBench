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
struct TYPE_2__ {scalar_t__ size; } ;
struct sram_partition {scalar_t__ pool; TYPE_1__ battr; } ;
struct sram_dev {int partitions; int /*<<< orphan*/  dev; struct sram_partition* partition; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_remove_bin_file (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ gen_pool_avail (scalar_t__) ; 
 scalar_t__ gen_pool_size (scalar_t__) ; 

__attribute__((used)) static void sram_free_partitions(struct sram_dev *sram)
{
	struct sram_partition *part;

	if (!sram->partitions)
		return;

	part = &sram->partition[sram->partitions - 1];
	for (; sram->partitions; sram->partitions--, part--) {
		if (part->battr.size)
			device_remove_bin_file(sram->dev, &part->battr);

		if (part->pool &&
		    gen_pool_avail(part->pool) < gen_pool_size(part->pool))
			dev_err(sram->dev, "removed pool while SRAM allocated\n");
	}
}