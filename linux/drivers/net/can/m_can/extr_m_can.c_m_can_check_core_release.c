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
typedef  int u8 ;
typedef  int u32 ;
struct m_can_classdev {int dummy; } ;

/* Variables and functions */
 int CREL_REL_MASK ; 
 int CREL_REL_SHIFT ; 
 int CREL_STEP_MASK ; 
 int CREL_STEP_SHIFT ; 
 int /*<<< orphan*/  M_CAN_CREL ; 
 int m_can_read (struct m_can_classdev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int m_can_check_core_release(struct m_can_classdev *cdev)
{
	u32 crel_reg;
	u8 rel;
	u8 step;
	int res;

	/* Read Core Release Version and split into version number
	 * Example: Version 3.2.1 => rel = 3; step = 2; substep = 1;
	 */
	crel_reg = m_can_read(cdev, M_CAN_CREL);
	rel = (u8)((crel_reg & CREL_REL_MASK) >> CREL_REL_SHIFT);
	step = (u8)((crel_reg & CREL_STEP_MASK) >> CREL_STEP_SHIFT);

	if (rel == 3) {
		/* M_CAN v3.x.y: create return value */
		res = 30 + step;
	} else {
		/* Unsupported M_CAN version */
		res = 0;
	}

	return res;
}