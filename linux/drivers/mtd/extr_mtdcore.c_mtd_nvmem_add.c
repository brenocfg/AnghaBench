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
struct nvmem_config {int id; int word_size; int stride; int read_only; int root_only; int no_of_node; struct mtd_info* priv; int /*<<< orphan*/  size; int /*<<< orphan*/  reg_read; int /*<<< orphan*/  owner; int /*<<< orphan*/  name; int /*<<< orphan*/ * dev; } ;
struct mtd_info {int /*<<< orphan*/ * nvmem; int /*<<< orphan*/  dev; int /*<<< orphan*/  size; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mtd_nvmem_reg_read ; 
 int /*<<< orphan*/ * nvmem_register (struct nvmem_config*) ; 

__attribute__((used)) static int mtd_nvmem_add(struct mtd_info *mtd)
{
	struct nvmem_config config = {};

	config.id = -1;
	config.dev = &mtd->dev;
	config.name = mtd->name;
	config.owner = THIS_MODULE;
	config.reg_read = mtd_nvmem_reg_read;
	config.size = mtd->size;
	config.word_size = 1;
	config.stride = 1;
	config.read_only = true;
	config.root_only = true;
	config.no_of_node = true;
	config.priv = mtd;

	mtd->nvmem = nvmem_register(&config);
	if (IS_ERR(mtd->nvmem)) {
		/* Just ignore if there is no NVMEM support in the kernel */
		if (PTR_ERR(mtd->nvmem) == -EOPNOTSUPP) {
			mtd->nvmem = NULL;
		} else {
			dev_err(&mtd->dev, "Failed to register NVMEM device\n");
			return PTR_ERR(mtd->nvmem);
		}
	}

	return 0;
}