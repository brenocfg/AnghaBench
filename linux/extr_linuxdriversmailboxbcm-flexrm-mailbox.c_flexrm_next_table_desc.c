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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DESC_ENC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DESC_TYPE_MASK ; 
 int /*<<< orphan*/  DESC_TYPE_SHIFT ; 
 int /*<<< orphan*/  NPTR_ADDR_MASK ; 
 int /*<<< orphan*/  NPTR_ADDR_SHIFT ; 
 int /*<<< orphan*/  NPTR_TOGGLE_MASK ; 
 int /*<<< orphan*/  NPTR_TOGGLE_SHIFT ; 
 int /*<<< orphan*/  NPTR_TYPE ; 

__attribute__((used)) static u64 flexrm_next_table_desc(u32 toggle, dma_addr_t next_addr)
{
	u64 desc = 0;

	DESC_ENC(desc, NPTR_TYPE, DESC_TYPE_SHIFT, DESC_TYPE_MASK);
	DESC_ENC(desc, toggle, NPTR_TOGGLE_SHIFT, NPTR_TOGGLE_MASK);
	DESC_ENC(desc, next_addr, NPTR_ADDR_SHIFT, NPTR_ADDR_MASK);

	return desc;
}