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
struct enetc_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENETC_MMCSR ; 
 int ENETC_MMCSR_ME ; 
 int /*<<< orphan*/  ENETC_PFPMR ; 
 int ENETC_PFPMR_MWLM ; 
 int ENETC_PFPMR_PMACE ; 
 int enetc_port_rd (struct enetc_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enetc_port_wr (struct enetc_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void enetc_configure_port_pmac(struct enetc_hw *hw)
{
	u32 temp;

	/* Set pMAC step lock */
	temp = enetc_port_rd(hw, ENETC_PFPMR);
	enetc_port_wr(hw, ENETC_PFPMR,
		      temp | ENETC_PFPMR_PMACE | ENETC_PFPMR_MWLM);

	temp = enetc_port_rd(hw, ENETC_MMCSR);
	enetc_port_wr(hw, ENETC_MMCSR, temp | ENETC_MMCSR_ME);
}