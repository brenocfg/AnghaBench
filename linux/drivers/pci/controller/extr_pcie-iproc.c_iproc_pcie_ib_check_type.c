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
struct iproc_pcie_ib_map {int type; } ;
typedef  enum iproc_pcie_ib_map_type { ____Placeholder_iproc_pcie_ib_map_type } iproc_pcie_ib_map_type ;

/* Variables and functions */

__attribute__((used)) static inline bool iproc_pcie_ib_check_type(const struct iproc_pcie_ib_map *ib_map,
					    enum iproc_pcie_ib_map_type type)
{
	return !!(ib_map->type == type);
}