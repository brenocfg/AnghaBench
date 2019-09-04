#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sram_reserve {int /*<<< orphan*/  size; } ;
struct TYPE_4__ {int mode; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  size; int /*<<< orphan*/  write; int /*<<< orphan*/  read; TYPE_1__ attr; } ;
struct sram_partition {TYPE_2__ battr; } ;
struct sram_dev {int /*<<< orphan*/  dev; } ;
typedef  scalar_t__ phys_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int device_create_bin_file (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  devm_kasprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned long long) ; 
 int /*<<< orphan*/  sram_read ; 
 int /*<<< orphan*/  sram_write ; 
 int /*<<< orphan*/  sysfs_bin_attr_init (TYPE_2__*) ; 

__attribute__((used)) static int sram_add_export(struct sram_dev *sram, struct sram_reserve *block,
			   phys_addr_t start, struct sram_partition *part)
{
	sysfs_bin_attr_init(&part->battr);
	part->battr.attr.name = devm_kasprintf(sram->dev, GFP_KERNEL,
					       "%llx.sram",
					       (unsigned long long)start);
	if (!part->battr.attr.name)
		return -ENOMEM;

	part->battr.attr.mode = S_IRUSR | S_IWUSR;
	part->battr.read = sram_read;
	part->battr.write = sram_write;
	part->battr.size = block->size;

	return device_create_bin_file(sram->dev, &part->battr);
}