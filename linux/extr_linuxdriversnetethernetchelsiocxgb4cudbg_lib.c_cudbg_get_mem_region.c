#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  size_t u32 ;
struct cudbg_meminfo {size_t mem_c; TYPE_2__* mem; TYPE_1__* avail; } ;
struct cudbg_mem_desc {int dummy; } ;
struct adapter {int dummy; } ;
struct TYPE_4__ {size_t idx; scalar_t__ limit; scalar_t__ base; } ;
struct TYPE_3__ {scalar_t__ base; scalar_t__ limit; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int cudbg_meminfo_get_mem_index (struct adapter*,struct cudbg_meminfo*,size_t,size_t*) ; 
 int /*<<< orphan*/ * cudbg_region ; 
 int /*<<< orphan*/  memcpy (struct cudbg_mem_desc*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int cudbg_get_mem_region(struct adapter *padap,
				struct cudbg_meminfo *meminfo,
				u8 mem_type, const char *region_name,
				struct cudbg_mem_desc *mem_desc)
{
	u8 mc, found = 0;
	u32 i, idx = 0;
	int rc;

	rc = cudbg_meminfo_get_mem_index(padap, meminfo, mem_type, &mc);
	if (rc)
		return rc;

	for (i = 0; i < ARRAY_SIZE(cudbg_region); i++) {
		if (!strcmp(cudbg_region[i], region_name)) {
			found = 1;
			idx = i;
			break;
		}
	}
	if (!found)
		return -EINVAL;

	found = 0;
	for (i = 0; i < meminfo->mem_c; i++) {
		if (meminfo->mem[i].idx >= ARRAY_SIZE(cudbg_region))
			continue; /* Skip holes */

		if (!(meminfo->mem[i].limit))
			meminfo->mem[i].limit =
				i < meminfo->mem_c - 1 ?
				meminfo->mem[i + 1].base - 1 : ~0;

		if (meminfo->mem[i].idx == idx) {
			/* Check if the region exists in @mem_type memory */
			if (meminfo->mem[i].base < meminfo->avail[mc].base &&
			    meminfo->mem[i].limit < meminfo->avail[mc].base)
				return -EINVAL;

			if (meminfo->mem[i].base > meminfo->avail[mc].limit)
				return -EINVAL;

			memcpy(mem_desc, &meminfo->mem[i],
			       sizeof(struct cudbg_mem_desc));
			found = 1;
			break;
		}
	}
	if (!found)
		return -EINVAL;

	return 0;
}