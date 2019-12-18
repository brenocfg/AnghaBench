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

/* Variables and functions */
#define  CCN_TYPE_RND_1P 133 
#define  CCN_TYPE_RND_2P 132 
#define  CCN_TYPE_RND_3P 131 
#define  CCN_TYPE_RNI_1P 130 
#define  CCN_TYPE_RNI_2P 129 
#define  CCN_TYPE_RNI_3P 128 

__attribute__((used)) static int arm_ccn_pmu_type_eq(u32 a, u32 b)
{
	if (a == b)
		return 1;

	switch (a) {
	case CCN_TYPE_RNI_1P:
	case CCN_TYPE_RNI_2P:
	case CCN_TYPE_RNI_3P:
	case CCN_TYPE_RND_1P:
	case CCN_TYPE_RND_2P:
	case CCN_TYPE_RND_3P:
		switch (b) {
		case CCN_TYPE_RNI_1P:
		case CCN_TYPE_RNI_2P:
		case CCN_TYPE_RNI_3P:
		case CCN_TYPE_RND_1P:
		case CCN_TYPE_RND_2P:
		case CCN_TYPE_RND_3P:
			return 1;
		}
		break;
	}

	return 0;
}