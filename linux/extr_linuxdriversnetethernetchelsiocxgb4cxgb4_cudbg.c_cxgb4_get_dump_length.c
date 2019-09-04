#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct adapter {int dummy; } ;
struct TYPE_4__ {int entity; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int CUDBG_DUMP_BUFF_SIZE ; 
 int CXGB4_ETH_DUMP_HW ; 
 int CXGB4_ETH_DUMP_MEM ; 
 int cudbg_get_workspace_size () ; 
 TYPE_1__* cxgb4_collect_hw_dump ; 
 TYPE_1__* cxgb4_collect_mem_dump ; 
 int cxgb4_get_entity_length (struct adapter*,int) ; 

u32 cxgb4_get_dump_length(struct adapter *adap, u32 flag)
{
	u32 i, entity;
	u32 len = 0;
	u32 wsize;

	if (flag & CXGB4_ETH_DUMP_HW) {
		for (i = 0; i < ARRAY_SIZE(cxgb4_collect_hw_dump); i++) {
			entity = cxgb4_collect_hw_dump[i].entity;
			len += cxgb4_get_entity_length(adap, entity);
		}
	}

	if (flag & CXGB4_ETH_DUMP_MEM) {
		for (i = 0; i < ARRAY_SIZE(cxgb4_collect_mem_dump); i++) {
			entity = cxgb4_collect_mem_dump[i].entity;
			len += cxgb4_get_entity_length(adap, entity);
		}
	}

	/* If compression is enabled, a smaller destination buffer is enough */
	wsize = cudbg_get_workspace_size();
	if (wsize && len > CUDBG_DUMP_BUFF_SIZE)
		len = CUDBG_DUMP_BUFF_SIZE;

	return len;
}