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
struct fjes_hw {int dummy; } ;
typedef  enum REG_ICTL_MASK { ____Placeholder_REG_ICTL_MASK } REG_ICTL_MASK ;

/* Variables and functions */
 int /*<<< orphan*/  XSCT_IG ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int fjes_hw_raise_interrupt(struct fjes_hw *hw, int dest_epid,
			    enum REG_ICTL_MASK  mask)
{
	u32 ig = mask | dest_epid;

	wr32(XSCT_IG, cpu_to_le32(ig));

	return 0;
}