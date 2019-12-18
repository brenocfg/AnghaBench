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
struct rcmm_dec {int count; void* state; int /*<<< orphan*/  bits; } ;
struct rc_dev {int enabled_protocols; } ;

/* Variables and functions */
 int RC_PROTO_BIT_RCMM12 ; 
 int RC_PROTO_BIT_RCMM24 ; 
 int /*<<< orphan*/  RC_PROTO_RCMM12 ; 
 int /*<<< orphan*/  RC_PROTO_RCMM24 ; 
 void* STATE_INACTIVE ; 
 int /*<<< orphan*/  rc_keydown (struct rc_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rcmm_miscmode(struct rc_dev *dev, struct rcmm_dec *data)
{
	switch (data->count) {
	case 24:
		if (dev->enabled_protocols & RC_PROTO_BIT_RCMM24) {
			rc_keydown(dev, RC_PROTO_RCMM24, data->bits, 0);
			data->state = STATE_INACTIVE;
			return 0;
		}
		return -1;

	case 12:
		if (dev->enabled_protocols & RC_PROTO_BIT_RCMM12) {
			rc_keydown(dev, RC_PROTO_RCMM12, data->bits, 0);
			data->state = STATE_INACTIVE;
			return 0;
		}
		return -1;
	}

	return -1;
}