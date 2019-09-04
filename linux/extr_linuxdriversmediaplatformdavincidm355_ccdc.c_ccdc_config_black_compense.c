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
struct ccdc_black_compensation {int b; int gb; int gr; int r; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLKCMP0 ; 
 int /*<<< orphan*/  BLKCMP1 ; 
 int CCDC_BLK_COMP_GB_COMP_SHIFT ; 
 int CCDC_BLK_COMP_GR_COMP_SHIFT ; 
 int CCDC_BLK_COMP_MASK ; 
 int CCDC_BLK_COMP_R_COMP_SHIFT ; 
 int /*<<< orphan*/  regw (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ccdc_config_black_compense(struct ccdc_black_compensation *bcomp)
{
	u32 val;

	val = (bcomp->b & CCDC_BLK_COMP_MASK) |
		((bcomp->gb & CCDC_BLK_COMP_MASK) <<
		CCDC_BLK_COMP_GB_COMP_SHIFT);
	regw(val, BLKCMP1);

	val = ((bcomp->gr & CCDC_BLK_COMP_MASK) <<
		CCDC_BLK_COMP_GR_COMP_SHIFT) |
		((bcomp->r & CCDC_BLK_COMP_MASK) <<
		CCDC_BLK_COMP_R_COMP_SHIFT);
	regw(val, BLKCMP0);
}