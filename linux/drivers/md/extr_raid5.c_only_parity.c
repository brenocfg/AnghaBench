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
#define  ALGORITHM_LEFT_ASYMMETRIC_6 134 
#define  ALGORITHM_LEFT_SYMMETRIC_6 133 
#define  ALGORITHM_PARITY_0 132 
#define  ALGORITHM_PARITY_0_6 131 
#define  ALGORITHM_PARITY_N 130 
#define  ALGORITHM_RIGHT_ASYMMETRIC_6 129 
#define  ALGORITHM_RIGHT_SYMMETRIC_6 128 

__attribute__((used)) static int only_parity(int raid_disk, int algo, int raid_disks, int max_degraded)
{
	switch (algo) {
	case ALGORITHM_PARITY_0:
		if (raid_disk < max_degraded)
			return 1;
		break;
	case ALGORITHM_PARITY_N:
		if (raid_disk >= raid_disks - max_degraded)
			return 1;
		break;
	case ALGORITHM_PARITY_0_6:
		if (raid_disk == 0 ||
		    raid_disk == raid_disks - 1)
			return 1;
		break;
	case ALGORITHM_LEFT_ASYMMETRIC_6:
	case ALGORITHM_RIGHT_ASYMMETRIC_6:
	case ALGORITHM_LEFT_SYMMETRIC_6:
	case ALGORITHM_RIGHT_SYMMETRIC_6:
		if (raid_disk == raid_disks - 1)
			return 1;
	}
	return 0;
}