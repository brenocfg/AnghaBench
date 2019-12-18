#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct hns3_enet_tqp_vector {int /*<<< orphan*/  last_jiffies; } ;
struct TYPE_3__ {scalar_t__ int_gl; int flow_level; } ;
struct hns3_enet_ring_group {scalar_t__ total_packets; TYPE_1__ coal; TYPE_2__* ring; } ;
struct TYPE_4__ {struct hns3_enet_tqp_vector* tqp_vector; } ;

/* Variables and functions */
#define  HNS3_FLOW_HIGH 131 
#define  HNS3_FLOW_LOW 130 
#define  HNS3_FLOW_MID 129 
#define  HNS3_FLOW_ULTRA 128 
 scalar_t__ HNS3_INT_GL_18K ; 
 scalar_t__ HNS3_INT_GL_20K ; 
 void* HNS3_INT_GL_50K ; 
 scalar_t__ HNS3_INT_GL_8K ; 
 int /*<<< orphan*/  hns3_get_new_flow_lvl (struct hns3_enet_ring_group*) ; 

__attribute__((used)) static bool hns3_get_new_int_gl(struct hns3_enet_ring_group *ring_group)
{
	struct hns3_enet_tqp_vector *tqp_vector;
	u16 new_int_gl;

	if (!ring_group->ring)
		return false;

	tqp_vector = ring_group->ring->tqp_vector;
	if (!tqp_vector->last_jiffies)
		return false;

	if (ring_group->total_packets == 0) {
		ring_group->coal.int_gl = HNS3_INT_GL_50K;
		ring_group->coal.flow_level = HNS3_FLOW_LOW;
		return true;
	}

	if (!hns3_get_new_flow_lvl(ring_group))
		return false;

	new_int_gl = ring_group->coal.int_gl;
	switch (ring_group->coal.flow_level) {
	case HNS3_FLOW_LOW:
		new_int_gl = HNS3_INT_GL_50K;
		break;
	case HNS3_FLOW_MID:
		new_int_gl = HNS3_INT_GL_20K;
		break;
	case HNS3_FLOW_HIGH:
		new_int_gl = HNS3_INT_GL_18K;
		break;
	case HNS3_FLOW_ULTRA:
		new_int_gl = HNS3_INT_GL_8K;
		break;
	default:
		break;
	}

	if (new_int_gl != ring_group->coal.int_gl) {
		ring_group->coal.int_gl = new_int_gl;
		return true;
	}
	return false;
}