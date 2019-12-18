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
struct slgt_info {int dummy; } ;

/* Variables and functions */
 int BIT0 ; 
 int /*<<< orphan*/  BIT1 ; 
 int /*<<< orphan*/  RDCSR ; 
 int rd_reg32 (struct slgt_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr_reg32 (struct slgt_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rdma_reset(struct slgt_info *info)
{
	unsigned int i;

	/* set reset bit */
	wr_reg32(info, RDCSR, BIT1);

	/* wait for enable bit cleared */
	for(i=0 ; i < 1000 ; i++)
		if (!(rd_reg32(info, RDCSR) & BIT0))
			break;
}