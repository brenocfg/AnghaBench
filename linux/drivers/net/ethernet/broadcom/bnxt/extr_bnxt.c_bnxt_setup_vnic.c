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
typedef  int /*<<< orphan*/  u16 ;
struct bnxt {int flags; } ;

/* Variables and functions */
 int BNXT_FLAG_CHIP_P5 ; 
 int __bnxt_setup_vnic (struct bnxt*,int /*<<< orphan*/ ) ; 
 int __bnxt_setup_vnic_p5 (struct bnxt*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnxt_setup_vnic(struct bnxt *bp, u16 vnic_id)
{
	if (bp->flags & BNXT_FLAG_CHIP_P5)
		return __bnxt_setup_vnic_p5(bp, vnic_id);
	else
		return __bnxt_setup_vnic(bp, vnic_id);
}