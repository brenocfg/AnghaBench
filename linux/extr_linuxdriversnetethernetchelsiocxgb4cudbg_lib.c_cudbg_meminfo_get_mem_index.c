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
typedef  int u8 ;
struct cudbg_meminfo {int avail_c; TYPE_1__* avail; } ;
struct TYPE_4__ {int /*<<< orphan*/  chip; } ;
struct adapter {TYPE_2__ params; } ;
struct TYPE_3__ {int idx; } ;

/* Variables and functions */
 int CUDBG_STATUS_ENTITY_NOT_FOUND ; 
 int EDC0_FLAG ; 
 int EDC1_FLAG ; 
 int HMA_FLAG ; 
 int MC0_FLAG ; 
 int MC1_FLAG ; 
 int MC_FLAG ; 
#define  MEM_EDC0 132 
#define  MEM_EDC1 131 
#define  MEM_HMA 130 
#define  MEM_MC0 129 
#define  MEM_MC1 128 
 int /*<<< orphan*/  is_t5 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cudbg_meminfo_get_mem_index(struct adapter *padap,
				       struct cudbg_meminfo *mem_info,
				       u8 mem_type, u8 *idx)
{
	u8 i, flag;

	switch (mem_type) {
	case MEM_EDC0:
		flag = EDC0_FLAG;
		break;
	case MEM_EDC1:
		flag = EDC1_FLAG;
		break;
	case MEM_MC0:
		/* Some T5 cards have both MC0 and MC1. */
		flag = is_t5(padap->params.chip) ? MC0_FLAG : MC_FLAG;
		break;
	case MEM_MC1:
		flag = MC1_FLAG;
		break;
	case MEM_HMA:
		flag = HMA_FLAG;
		break;
	default:
		return CUDBG_STATUS_ENTITY_NOT_FOUND;
	}

	for (i = 0; i < mem_info->avail_c; i++) {
		if (mem_info->avail[i].idx == flag) {
			*idx = i;
			return 0;
		}
	}

	return CUDBG_STATUS_ENTITY_NOT_FOUND;
}