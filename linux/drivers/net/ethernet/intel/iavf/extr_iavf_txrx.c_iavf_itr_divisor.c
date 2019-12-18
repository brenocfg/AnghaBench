#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct iavf_q_vector {TYPE_1__* adapter; } ;
struct TYPE_2__ {int link_speed; } ;

/* Variables and functions */
 int IAVF_ITR_ADAPTIVE_MIN_INC ; 
#define  IAVF_LINK_SPEED_100MB 133 
#define  IAVF_LINK_SPEED_10GB 132 
#define  IAVF_LINK_SPEED_1GB 131 
#define  IAVF_LINK_SPEED_20GB 130 
#define  IAVF_LINK_SPEED_25GB 129 
#define  IAVF_LINK_SPEED_40GB 128 

__attribute__((used)) static inline unsigned int iavf_itr_divisor(struct iavf_q_vector *q_vector)
{
	unsigned int divisor;

	switch (q_vector->adapter->link_speed) {
	case IAVF_LINK_SPEED_40GB:
		divisor = IAVF_ITR_ADAPTIVE_MIN_INC * 1024;
		break;
	case IAVF_LINK_SPEED_25GB:
	case IAVF_LINK_SPEED_20GB:
		divisor = IAVF_ITR_ADAPTIVE_MIN_INC * 512;
		break;
	default:
	case IAVF_LINK_SPEED_10GB:
		divisor = IAVF_ITR_ADAPTIVE_MIN_INC * 256;
		break;
	case IAVF_LINK_SPEED_1GB:
	case IAVF_LINK_SPEED_100MB:
		divisor = IAVF_ITR_ADAPTIVE_MIN_INC * 32;
		break;
	}

	return divisor;
}