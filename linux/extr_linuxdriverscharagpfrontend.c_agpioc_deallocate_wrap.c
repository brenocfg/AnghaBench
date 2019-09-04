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
struct agp_memory {int dummy; } ;
struct agp_file_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int EINVAL ; 
 struct agp_memory* agp_find_mem_by_key (int) ; 
 int /*<<< orphan*/  agp_free_memory_wrap (struct agp_memory*) ; 

int agpioc_deallocate_wrap(struct agp_file_private *priv, int arg)
{
	struct agp_memory *memory;

	DBG("");
	memory = agp_find_mem_by_key(arg);

	if (memory == NULL)
		return -EINVAL;

	agp_free_memory_wrap(memory);
	return 0;
}