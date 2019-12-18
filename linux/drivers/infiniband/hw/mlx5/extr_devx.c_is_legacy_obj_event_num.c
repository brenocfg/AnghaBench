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
typedef  int u16 ;

/* Variables and functions */
#define  MLX5_EVENT_TYPE_COMM_EST 142 
#define  MLX5_EVENT_TYPE_COMP 141 
#define  MLX5_EVENT_TYPE_CQ_ERROR 140 
#define  MLX5_EVENT_TYPE_DCT_DRAINED 139 
#define  MLX5_EVENT_TYPE_DCT_KEY_VIOLATION 138 
#define  MLX5_EVENT_TYPE_PATH_MIG 137 
#define  MLX5_EVENT_TYPE_PATH_MIG_FAILED 136 
#define  MLX5_EVENT_TYPE_SQ_DRAINED 135 
#define  MLX5_EVENT_TYPE_SRQ_CATAS_ERROR 134 
#define  MLX5_EVENT_TYPE_SRQ_LAST_WQE 133 
#define  MLX5_EVENT_TYPE_SRQ_RQ_LIMIT 132 
#define  MLX5_EVENT_TYPE_WQ_ACCESS_ERROR 131 
#define  MLX5_EVENT_TYPE_WQ_CATAS_ERROR 130 
#define  MLX5_EVENT_TYPE_WQ_INVAL_REQ_ERROR 129 
#define  MLX5_EVENT_TYPE_XRQ_ERROR 128 

__attribute__((used)) static bool is_legacy_obj_event_num(u16 event_num)
{
	switch (event_num) {
	case MLX5_EVENT_TYPE_PATH_MIG:
	case MLX5_EVENT_TYPE_COMM_EST:
	case MLX5_EVENT_TYPE_SQ_DRAINED:
	case MLX5_EVENT_TYPE_SRQ_LAST_WQE:
	case MLX5_EVENT_TYPE_SRQ_RQ_LIMIT:
	case MLX5_EVENT_TYPE_CQ_ERROR:
	case MLX5_EVENT_TYPE_WQ_CATAS_ERROR:
	case MLX5_EVENT_TYPE_PATH_MIG_FAILED:
	case MLX5_EVENT_TYPE_WQ_INVAL_REQ_ERROR:
	case MLX5_EVENT_TYPE_WQ_ACCESS_ERROR:
	case MLX5_EVENT_TYPE_SRQ_CATAS_ERROR:
	case MLX5_EVENT_TYPE_DCT_DRAINED:
	case MLX5_EVENT_TYPE_COMP:
	case MLX5_EVENT_TYPE_DCT_KEY_VIOLATION:
	case MLX5_EVENT_TYPE_XRQ_ERROR:
		return true;
	default:
		return false;
	}
}