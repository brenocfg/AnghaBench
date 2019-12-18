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
typedef  int u32 ;

/* Variables and functions */
 int CUDBG_QTYPE_RDMA_CIQ ; 
 int CUDBG_QTYPE_UNKNOWN ; 
#define  CXGB4_ULD_RDMA 128 

__attribute__((used)) static inline u32 cudbg_uld_ciq_to_qtype(u32 uld)
{
	switch (uld) {
	case CXGB4_ULD_RDMA:
		return CUDBG_QTYPE_RDMA_CIQ;
	}

	return CUDBG_QTYPE_UNKNOWN;
}