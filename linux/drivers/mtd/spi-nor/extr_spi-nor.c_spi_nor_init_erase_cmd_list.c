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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct spi_nor_erase_type {int dummy; } ;
struct spi_nor_erase_region {int offset; scalar_t__ size; int /*<<< orphan*/  count; int /*<<< orphan*/  list; } ;
struct spi_nor_erase_map {int dummy; } ;
struct spi_nor_erase_command {int offset; scalar_t__ size; int /*<<< orphan*/  count; int /*<<< orphan*/  list; } ;
struct TYPE_2__ {struct spi_nor_erase_map erase_map; } ;
struct spi_nor {TYPE_1__ params; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct spi_nor_erase_region*) ; 
 int PTR_ERR (struct spi_nor_erase_region*) ; 
 int SNOR_OVERLAID_REGION ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  spi_nor_destroy_erase_cmd_list (struct list_head*) ; 
 struct spi_nor_erase_type* spi_nor_find_best_erase_type (struct spi_nor_erase_map const*,struct spi_nor_erase_region*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct spi_nor_erase_region* spi_nor_find_erase_region (struct spi_nor_erase_map const*,scalar_t__) ; 
 struct spi_nor_erase_region* spi_nor_init_erase_cmd (struct spi_nor_erase_region*,struct spi_nor_erase_type const*) ; 
 scalar_t__ spi_nor_region_end (struct spi_nor_erase_region*) ; 
 struct spi_nor_erase_region* spi_nor_region_next (struct spi_nor_erase_region*) ; 

__attribute__((used)) static int spi_nor_init_erase_cmd_list(struct spi_nor *nor,
				       struct list_head *erase_list,
				       u64 addr, u32 len)
{
	const struct spi_nor_erase_map *map = &nor->params.erase_map;
	const struct spi_nor_erase_type *erase, *prev_erase = NULL;
	struct spi_nor_erase_region *region;
	struct spi_nor_erase_command *cmd = NULL;
	u64 region_end;
	int ret = -EINVAL;

	region = spi_nor_find_erase_region(map, addr);
	if (IS_ERR(region))
		return PTR_ERR(region);

	region_end = spi_nor_region_end(region);

	while (len) {
		erase = spi_nor_find_best_erase_type(map, region, addr, len);
		if (!erase)
			goto destroy_erase_cmd_list;

		if (prev_erase != erase ||
		    region->offset & SNOR_OVERLAID_REGION) {
			cmd = spi_nor_init_erase_cmd(region, erase);
			if (IS_ERR(cmd)) {
				ret = PTR_ERR(cmd);
				goto destroy_erase_cmd_list;
			}

			list_add_tail(&cmd->list, erase_list);
		} else {
			cmd->count++;
		}

		addr += cmd->size;
		len -= cmd->size;

		if (len && addr >= region_end) {
			region = spi_nor_region_next(region);
			if (!region)
				goto destroy_erase_cmd_list;
			region_end = spi_nor_region_end(region);
		}

		prev_erase = erase;
	}

	return 0;

destroy_erase_cmd_list:
	spi_nor_destroy_erase_cmd_list(erase_list);
	return ret;
}