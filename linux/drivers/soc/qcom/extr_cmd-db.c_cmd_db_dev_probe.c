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
struct reserved_mem {int /*<<< orphan*/  size; int /*<<< orphan*/  base; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MEMREMAP_WB ; 
 int /*<<< orphan*/ * cmd_db_header ; 
 int /*<<< orphan*/  cmd_db_magic_matches (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/ * memremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct reserved_mem* of_reserved_mem_lookup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cmd_db_dev_probe(struct platform_device *pdev)
{
	struct reserved_mem *rmem;
	int ret = 0;

	rmem = of_reserved_mem_lookup(pdev->dev.of_node);
	if (!rmem) {
		dev_err(&pdev->dev, "failed to acquire memory region\n");
		return -EINVAL;
	}

	cmd_db_header = memremap(rmem->base, rmem->size, MEMREMAP_WB);
	if (!cmd_db_header) {
		ret = -ENOMEM;
		cmd_db_header = NULL;
		return ret;
	}

	if (!cmd_db_magic_matches(cmd_db_header)) {
		dev_err(&pdev->dev, "Invalid Command DB Magic\n");
		return -EINVAL;
	}

	return 0;
}