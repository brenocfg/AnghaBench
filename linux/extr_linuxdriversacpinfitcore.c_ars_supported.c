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
struct nvdimm_bus_descriptor {unsigned long const cmd_mask; } ;
struct nvdimm_bus {int dummy; } ;

/* Variables and functions */
 int ND_CMD_ARS_CAP ; 
 int ND_CMD_ARS_START ; 
 int ND_CMD_ARS_STATUS ; 
 struct nvdimm_bus_descriptor* to_nd_desc (struct nvdimm_bus*) ; 

__attribute__((used)) static bool ars_supported(struct nvdimm_bus *nvdimm_bus)
{
	struct nvdimm_bus_descriptor *nd_desc = to_nd_desc(nvdimm_bus);
	const unsigned long mask = 1 << ND_CMD_ARS_CAP | 1 << ND_CMD_ARS_START
		| 1 << ND_CMD_ARS_STATUS;

	return (nd_desc->cmd_mask & mask) == mask;
}