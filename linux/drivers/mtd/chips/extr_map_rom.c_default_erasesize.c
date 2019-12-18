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
struct map_info {unsigned int size; int /*<<< orphan*/  device_node; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 unsigned int be32_to_cpu (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/ * of_get_property (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int default_erasesize(struct map_info *map)
{
	const __be32 *erase_size = NULL;

	erase_size = of_get_property(map->device_node, "erase-size", NULL);

	return !erase_size ? map->size : be32_to_cpu(*erase_size);
}