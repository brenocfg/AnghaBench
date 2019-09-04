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
struct bnx2x_queue_sp_obj {int state; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int BNX2X_Q_LOGICAL_STATE_ACTIVE ; 
 int BNX2X_Q_LOGICAL_STATE_STOPPED ; 
#define  BNX2X_Q_STATE_ACTIVE 136 
#define  BNX2X_Q_STATE_FLRED 135 
#define  BNX2X_Q_STATE_INACTIVE 134 
#define  BNX2X_Q_STATE_INITIALIZED 133 
#define  BNX2X_Q_STATE_MCOS_TERMINATED 132 
#define  BNX2X_Q_STATE_MULTI_COS 131 
#define  BNX2X_Q_STATE_RESET 130 
#define  BNX2X_Q_STATE_STOPPED 129 
#define  BNX2X_Q_STATE_TERMINATED 128 
 int EINVAL ; 

int bnx2x_get_q_logical_state(struct bnx2x *bp,
			       struct bnx2x_queue_sp_obj *obj)
{
	switch (obj->state) {
	case BNX2X_Q_STATE_ACTIVE:
	case BNX2X_Q_STATE_MULTI_COS:
		return BNX2X_Q_LOGICAL_STATE_ACTIVE;
	case BNX2X_Q_STATE_RESET:
	case BNX2X_Q_STATE_INITIALIZED:
	case BNX2X_Q_STATE_MCOS_TERMINATED:
	case BNX2X_Q_STATE_INACTIVE:
	case BNX2X_Q_STATE_STOPPED:
	case BNX2X_Q_STATE_TERMINATED:
	case BNX2X_Q_STATE_FLRED:
		return BNX2X_Q_LOGICAL_STATE_STOPPED;
	default:
		return -EINVAL;
	}
}