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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct bnx2x {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 scalar_t__ XSEM_REG_FAST_MEMORY ; 
 scalar_t__ XSTORM_SPQ_PAGE_BASE_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __storm_memset_dma_mapping (struct bnx2x*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void storm_memset_spq_addr(struct bnx2x *bp,
				  dma_addr_t mapping, u16 abs_fid)
{
	u32 addr = XSEM_REG_FAST_MEMORY +
			XSTORM_SPQ_PAGE_BASE_OFFSET(abs_fid);

	__storm_memset_dma_mapping(bp, addr, mapping);
}