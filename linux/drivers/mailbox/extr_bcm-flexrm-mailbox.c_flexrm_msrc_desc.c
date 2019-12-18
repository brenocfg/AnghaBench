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
typedef  unsigned int dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DESC_ENC (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DESC_TYPE_MASK ; 
 int /*<<< orphan*/  DESC_TYPE_SHIFT ; 
 int /*<<< orphan*/  MSRC_ADDR_MASK ; 
 int /*<<< orphan*/  MSRC_ADDR_SHIFT ; 
 int /*<<< orphan*/  MSRC_LENGTH_MASK ; 
 int /*<<< orphan*/  MSRC_LENGTH_SHIFT ; 
 unsigned int MSRC_TYPE ; 

__attribute__((used)) static u64 flexrm_msrc_desc(dma_addr_t addr, unsigned int length_div_16)
{
	u64 desc = 0;

	DESC_ENC(desc, MSRC_TYPE, DESC_TYPE_SHIFT, DESC_TYPE_MASK);
	DESC_ENC(desc, length_div_16, MSRC_LENGTH_SHIFT, MSRC_LENGTH_MASK);
	DESC_ENC(desc, addr, MSRC_ADDR_SHIFT, MSRC_ADDR_MASK);

	return desc;
}