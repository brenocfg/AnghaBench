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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int IAVF_TXD_QW1_CMD_SHIFT ; 
 int IAVF_TXD_QW1_L2TAG1_SHIFT ; 
 int IAVF_TXD_QW1_OFFSET_SHIFT ; 
 int IAVF_TXD_QW1_TX_BUF_SZ_SHIFT ; 
 int IAVF_TX_DESC_DTYPE_DATA ; 
 int /*<<< orphan*/  cpu_to_le64 (int) ; 

__attribute__((used)) static inline __le64 build_ctob(u32 td_cmd, u32 td_offset, unsigned int size,
				u32 td_tag)
{
	return cpu_to_le64(IAVF_TX_DESC_DTYPE_DATA |
			   ((u64)td_cmd  << IAVF_TXD_QW1_CMD_SHIFT) |
			   ((u64)td_offset << IAVF_TXD_QW1_OFFSET_SHIFT) |
			   ((u64)size  << IAVF_TXD_QW1_TX_BUF_SZ_SHIFT) |
			   ((u64)td_tag  << IAVF_TXD_QW1_L2TAG1_SHIFT));
}