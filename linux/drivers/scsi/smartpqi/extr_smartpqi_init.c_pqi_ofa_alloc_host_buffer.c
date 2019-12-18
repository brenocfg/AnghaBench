#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct pqi_ctrl_info {TYPE_1__* pqi_ofa_mem_virt_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  bytes_allocated; } ;

/* Variables and functions */
 int ENOMEM ; 
 int PQI_OFA_MAX_SG_DESCRIPTORS ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pqi_ofa_alloc_mem (struct pqi_ctrl_info*,int,int) ; 

__attribute__((used)) static int pqi_ofa_alloc_host_buffer(struct pqi_ctrl_info *ctrl_info)
{
	u32 total_size;
	u32 min_chunk_size;
	u32 chunk_sz;

	total_size = le32_to_cpu(
			ctrl_info->pqi_ofa_mem_virt_addr->bytes_allocated);
	min_chunk_size = total_size / PQI_OFA_MAX_SG_DESCRIPTORS;

	for (chunk_sz = total_size; chunk_sz >= min_chunk_size; chunk_sz /= 2)
		if (!pqi_ofa_alloc_mem(ctrl_info, total_size, chunk_sz))
			return 0;

	return -ENOMEM;
}