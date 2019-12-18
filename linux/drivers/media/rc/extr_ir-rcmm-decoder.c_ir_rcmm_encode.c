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
typedef  int /*<<< orphan*/  u32 ;
struct ir_raw_event {int dummy; } ;
typedef  enum rc_proto { ____Placeholder_rc_proto } rc_proto ;

/* Variables and functions */
 int EINVAL ; 
#define  RC_PROTO_RCMM12 130 
#define  RC_PROTO_RCMM24 129 
#define  RC_PROTO_RCMM32 128 
 int ir_rcmm_rawencoder (struct ir_raw_event**,unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ir_rcmm_encode(enum rc_proto protocol, u32 scancode,
			  struct ir_raw_event *events, unsigned int max)
{
	struct ir_raw_event *e = events;
	int ret;

	switch (protocol) {
	case RC_PROTO_RCMM32:
		ret = ir_rcmm_rawencoder(&e, max, 32, scancode);
		break;
	case RC_PROTO_RCMM24:
		ret = ir_rcmm_rawencoder(&e, max, 24, scancode);
		break;
	case RC_PROTO_RCMM12:
		ret = ir_rcmm_rawencoder(&e, max, 12, scancode);
		break;
	default:
		ret = -EINVAL;
	}

	if (ret < 0)
		return ret;

	return e - events;
}