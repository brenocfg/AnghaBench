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
struct drxd_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ConfigureMPEGOutput (struct drxd_state*,int) ; 
 int /*<<< orphan*/  DRX_GetLockStatus (struct drxd_state*,int*) ; 
 int DRX_LOCK_FEC ; 

__attribute__((used)) static int DRXD_status(struct drxd_state *state, u32 *pLockStatus)
{
	DRX_GetLockStatus(state, pLockStatus);

	/*if (*pLockStatus&DRX_LOCK_MPEG) */
	if (*pLockStatus & DRX_LOCK_FEC) {
		ConfigureMPEGOutput(state, 1);
		/* Get status again, in case we have MPEG lock now */
		/*DRX_GetLockStatus(state, pLockStatus); */
	}

	return 0;
}