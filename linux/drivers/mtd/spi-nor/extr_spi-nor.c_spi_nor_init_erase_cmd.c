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
struct spi_nor_erase_type {int /*<<< orphan*/  size; int /*<<< orphan*/  opcode; } ;
struct spi_nor_erase_region {int offset; int /*<<< orphan*/  size; } ;
struct spi_nor_erase_command {int count; int /*<<< orphan*/  size; int /*<<< orphan*/  opcode; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct spi_nor_erase_command* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int SNOR_OVERLAID_REGION ; 
 struct spi_nor_erase_command* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct spi_nor_erase_command *
spi_nor_init_erase_cmd(const struct spi_nor_erase_region *region,
		       const struct spi_nor_erase_type *erase)
{
	struct spi_nor_erase_command *cmd;

	cmd = kmalloc(sizeof(*cmd), GFP_KERNEL);
	if (!cmd)
		return ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&cmd->list);
	cmd->opcode = erase->opcode;
	cmd->count = 1;

	if (region->offset & SNOR_OVERLAID_REGION)
		cmd->size = region->size;
	else
		cmd->size = erase->size;

	return cmd;
}