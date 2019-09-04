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

/* Variables and functions */
 int /*<<< orphan*/  PRCM_PLLDSI_LOCKP ; 
 int PRCM_PLLDSI_LOCKP_PRCM_PLLDSI_LOCKP10 ; 
 int PRCM_PLLDSI_LOCKP_PRCM_PLLDSI_LOCKP3 ; 
 int readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool plldsi_locked(void)
{
	return (readl(PRCM_PLLDSI_LOCKP) &
		(PRCM_PLLDSI_LOCKP_PRCM_PLLDSI_LOCKP10 |
		 PRCM_PLLDSI_LOCKP_PRCM_PLLDSI_LOCKP3)) ==
		(PRCM_PLLDSI_LOCKP_PRCM_PLLDSI_LOCKP10 |
		 PRCM_PLLDSI_LOCKP_PRCM_PLLDSI_LOCKP3);
}