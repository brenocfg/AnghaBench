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
struct fastrpc_map {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  fastrpc_free_map ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fastrpc_map_put(struct fastrpc_map *map)
{
	if (map)
		kref_put(&map->refcount, fastrpc_free_map);
}