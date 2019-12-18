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
 int /*<<< orphan*/  DSTT_ADDR_MASK ; 
 int /*<<< orphan*/  DSTT_ADDR_SHIFT ; 
 int /*<<< orphan*/  DSTT_LENGTH_MASK ; 
 int /*<<< orphan*/  DSTT_LENGTH_SHIFT ; 
 unsigned int DSTT_TYPE ; 

__attribute__((used)) static u64 flexrm_dstt_desc(dma_addr_t addr, unsigned int length)
{
	u64 desc = 0;

	DESC_ENC(desc, DSTT_TYPE, DESC_TYPE_SHIFT, DESC_TYPE_MASK);
	DESC_ENC(desc, length, DSTT_LENGTH_SHIFT, DSTT_LENGTH_MASK);
	DESC_ENC(desc, addr, DSTT_ADDR_SHIFT, DSTT_ADDR_MASK);

	return desc;
}