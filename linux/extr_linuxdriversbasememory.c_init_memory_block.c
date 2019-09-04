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
struct memory_block {int start_section_nr; int end_section_nr; unsigned long state; int /*<<< orphan*/  phys_device; } ;
struct mem_section {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int __section_nr (struct mem_section*) ; 
 int /*<<< orphan*/  arch_get_memory_phys_device (unsigned long) ; 
 int base_memory_block_id (int) ; 
 struct memory_block* kzalloc (int,int /*<<< orphan*/ ) ; 
 int register_memory (struct memory_block*) ; 
 unsigned long section_nr_to_pfn (int) ; 
 int sections_per_block ; 

__attribute__((used)) static int init_memory_block(struct memory_block **memory,
			     struct mem_section *section, unsigned long state)
{
	struct memory_block *mem;
	unsigned long start_pfn;
	int scn_nr;
	int ret = 0;

	mem = kzalloc(sizeof(*mem), GFP_KERNEL);
	if (!mem)
		return -ENOMEM;

	scn_nr = __section_nr(section);
	mem->start_section_nr =
			base_memory_block_id(scn_nr) * sections_per_block;
	mem->end_section_nr = mem->start_section_nr + sections_per_block - 1;
	mem->state = state;
	start_pfn = section_nr_to_pfn(mem->start_section_nr);
	mem->phys_device = arch_get_memory_phys_device(start_pfn);

	ret = register_memory(mem);

	*memory = mem;
	return ret;
}