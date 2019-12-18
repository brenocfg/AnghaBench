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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_FLEX_50_MASK ; 
 int /*<<< orphan*/  I40E_FLEX_51_MASK ; 
 int /*<<< orphan*/  I40E_FLEX_52_MASK ; 
 int /*<<< orphan*/  I40E_FLEX_53_MASK ; 
 int /*<<< orphan*/  I40E_FLEX_54_MASK ; 
 int /*<<< orphan*/  I40E_FLEX_55_MASK ; 
 int /*<<< orphan*/  I40E_FLEX_56_MASK ; 
 int /*<<< orphan*/  I40E_FLEX_57_MASK ; 

__attribute__((used)) static u64 i40e_pit_index_to_mask(int pit_index)
{
	switch (pit_index) {
	case 0:
		return I40E_FLEX_50_MASK;
	case 1:
		return I40E_FLEX_51_MASK;
	case 2:
		return I40E_FLEX_52_MASK;
	case 3:
		return I40E_FLEX_53_MASK;
	case 4:
		return I40E_FLEX_54_MASK;
	case 5:
		return I40E_FLEX_55_MASK;
	case 6:
		return I40E_FLEX_56_MASK;
	case 7:
		return I40E_FLEX_57_MASK;
	default:
		return 0;
	}
}