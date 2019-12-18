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
typedef  enum roce_mode { ____Placeholder_roce_mode } roce_mode ;
typedef  enum roce_flavor { ____Placeholder_roce_flavor } roce_flavor ;

/* Variables and functions */
 int MAX_ROCE_FLAVOR ; 
 int PLAIN_ROCE ; 
#define  ROCE_V1 130 
#define  ROCE_V2_IPV4 129 
#define  ROCE_V2_IPV6 128 
 int RROCE_IPV4 ; 
 int RROCE_IPV6 ; 

__attribute__((used)) static enum roce_flavor qed_roce_mode_to_flavor(enum roce_mode roce_mode)
{
	switch (roce_mode) {
	case ROCE_V1:
		return PLAIN_ROCE;
	case ROCE_V2_IPV4:
		return RROCE_IPV4;
	case ROCE_V2_IPV6:
		return RROCE_IPV6;
	default:
		return MAX_ROCE_FLAVOR;
	}
}