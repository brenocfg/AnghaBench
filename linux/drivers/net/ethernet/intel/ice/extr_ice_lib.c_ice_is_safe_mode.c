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
struct ice_pf {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_FLAG_ADV_FEATURES ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool ice_is_safe_mode(struct ice_pf *pf)
{
	return !test_bit(ICE_FLAG_ADV_FEATURES, pf->flags);
}