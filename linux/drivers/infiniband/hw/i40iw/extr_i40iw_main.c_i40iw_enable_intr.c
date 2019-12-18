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
struct i40iw_sc_dev {int /*<<< orphan*/  hw; scalar_t__ is_pf; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_PFINT_DYN_CTLN (int) ; 
 int I40E_PFINT_DYN_CTLN_CLEARPBA_MASK ; 
 int I40E_PFINT_DYN_CTLN_INTENA_MASK ; 
 int I40E_PFINT_DYN_CTLN_ITR_INDX_SHIFT ; 
 int /*<<< orphan*/  I40E_VFINT_DYN_CTLN1 (int) ; 
 int /*<<< orphan*/  i40iw_wr32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void i40iw_enable_intr(struct i40iw_sc_dev *dev, u32 msix_id)
{
	u32 val;

	val = I40E_PFINT_DYN_CTLN_INTENA_MASK |
		I40E_PFINT_DYN_CTLN_CLEARPBA_MASK |
		(3 << I40E_PFINT_DYN_CTLN_ITR_INDX_SHIFT);
	if (dev->is_pf)
		i40iw_wr32(dev->hw, I40E_PFINT_DYN_CTLN(msix_id - 1), val);
	else
		i40iw_wr32(dev->hw, I40E_VFINT_DYN_CTLN1(msix_id - 1), val);
}