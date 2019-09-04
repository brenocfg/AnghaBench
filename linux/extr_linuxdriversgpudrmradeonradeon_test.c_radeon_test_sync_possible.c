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
struct radeon_ring {scalar_t__ idx; } ;

/* Variables and functions */
 scalar_t__ TN_RING_TYPE_VCE1_INDEX ; 
 scalar_t__ TN_RING_TYPE_VCE2_INDEX ; 

__attribute__((used)) static bool radeon_test_sync_possible(struct radeon_ring *ringA,
				      struct radeon_ring *ringB)
{
	if (ringA->idx == TN_RING_TYPE_VCE2_INDEX &&
	    ringB->idx == TN_RING_TYPE_VCE1_INDEX)
		return false;

	return true;
}