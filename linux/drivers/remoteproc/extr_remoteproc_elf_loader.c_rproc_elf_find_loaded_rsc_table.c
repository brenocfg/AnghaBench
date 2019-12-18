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
struct rproc {int /*<<< orphan*/  dev; } ;
struct resource_table {int dummy; } ;
struct firmware {int /*<<< orphan*/  size; scalar_t__ data; } ;
struct elf32_shdr {int /*<<< orphan*/  sh_size; int /*<<< orphan*/  sh_addr; } ;
struct elf32_hdr {int dummy; } ;

/* Variables and functions */
 struct elf32_shdr* find_table (int /*<<< orphan*/ *,struct elf32_hdr*,int /*<<< orphan*/ ) ; 
 struct resource_table* rproc_da_to_va (struct rproc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct resource_table *rproc_elf_find_loaded_rsc_table(struct rproc *rproc,
						       const struct firmware *fw)
{
	struct elf32_hdr *ehdr = (struct elf32_hdr *)fw->data;
	struct elf32_shdr *shdr;

	shdr = find_table(&rproc->dev, ehdr, fw->size);
	if (!shdr)
		return NULL;

	return rproc_da_to_va(rproc, shdr->sh_addr, shdr->sh_size);
}