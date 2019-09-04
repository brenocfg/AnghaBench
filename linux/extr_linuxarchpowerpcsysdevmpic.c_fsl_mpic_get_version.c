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
struct mpic {int flags; int /*<<< orphan*/  thiscpuregs; int /*<<< orphan*/  reg_type; } ;

/* Variables and functions */
 int MPIC_FSL ; 
 int /*<<< orphan*/  MPIC_FSL_BRR1 ; 
 int MPIC_FSL_BRR1_VER ; 
 int _mpic_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 fsl_mpic_get_version(struct mpic *mpic)
{
	u32 brr1;

	if (!(mpic->flags & MPIC_FSL))
		return 0;

	brr1 = _mpic_read(mpic->reg_type, &mpic->thiscpuregs,
			MPIC_FSL_BRR1);

	return brr1 & MPIC_FSL_BRR1_VER;
}