#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct i40e_q_vector {TYPE_5__* vsi; } ;
struct TYPE_10__ {TYPE_4__* back; } ;
struct TYPE_6__ {int link_speed; } ;
struct TYPE_7__ {TYPE_1__ link_info; } ;
struct TYPE_8__ {TYPE_2__ phy; } ;
struct TYPE_9__ {TYPE_3__ hw; } ;

/* Variables and functions */
 int I40E_ITR_ADAPTIVE_MIN_INC ; 
#define  I40E_LINK_SPEED_100MB 133 
#define  I40E_LINK_SPEED_10GB 132 
#define  I40E_LINK_SPEED_1GB 131 
#define  I40E_LINK_SPEED_20GB 130 
#define  I40E_LINK_SPEED_25GB 129 
#define  I40E_LINK_SPEED_40GB 128 

__attribute__((used)) static inline unsigned int i40e_itr_divisor(struct i40e_q_vector *q_vector)
{
	unsigned int divisor;

	switch (q_vector->vsi->back->hw.phy.link_info.link_speed) {
	case I40E_LINK_SPEED_40GB:
		divisor = I40E_ITR_ADAPTIVE_MIN_INC * 1024;
		break;
	case I40E_LINK_SPEED_25GB:
	case I40E_LINK_SPEED_20GB:
		divisor = I40E_ITR_ADAPTIVE_MIN_INC * 512;
		break;
	default:
	case I40E_LINK_SPEED_10GB:
		divisor = I40E_ITR_ADAPTIVE_MIN_INC * 256;
		break;
	case I40E_LINK_SPEED_1GB:
	case I40E_LINK_SPEED_100MB:
		divisor = I40E_ITR_ADAPTIVE_MIN_INC * 32;
		break;
	}

	return divisor;
}