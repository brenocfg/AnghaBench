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
 int BIT (int) ; 
#define  MLX5_EVENT_QUEUE_TYPE_DCT 131 
#define  MLX5_EVENT_QUEUE_TYPE_QP 130 
#define  MLX5_EVENT_QUEUE_TYPE_RQ 129 
#define  MLX5_EVENT_QUEUE_TYPE_SQ 128 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int dct_allowed_event_types () ; 
 int qp_allowed_event_types () ; 
 int rq_allowed_event_types () ; 
 int sq_allowed_event_types () ; 

__attribute__((used)) static bool is_event_type_allowed(int rsc_type, int event_type)
{
	switch (rsc_type) {
	case MLX5_EVENT_QUEUE_TYPE_QP:
		return BIT(event_type) & qp_allowed_event_types();
	case MLX5_EVENT_QUEUE_TYPE_RQ:
		return BIT(event_type) & rq_allowed_event_types();
	case MLX5_EVENT_QUEUE_TYPE_SQ:
		return BIT(event_type) & sq_allowed_event_types();
	case MLX5_EVENT_QUEUE_TYPE_DCT:
		return BIT(event_type) & dct_allowed_event_types();
	default:
		WARN(1, "Event arrived for unknown resource type");
		return false;
	}
}