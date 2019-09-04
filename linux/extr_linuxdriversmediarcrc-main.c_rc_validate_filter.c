#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct rc_scancode_filter {int /*<<< orphan*/  mask; int /*<<< orphan*/  data; } ;
struct rc_dev {int wakeup_protocol; scalar_t__ encode_wakeup; } ;
typedef  enum rc_proto { ____Placeholder_rc_proto } rc_proto ;
struct TYPE_3__ {int /*<<< orphan*/  scancode_bits; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 TYPE_1__* protocols ; 
 int /*<<< orphan*/  rc_validate_scancode (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rc_validate_filter(struct rc_dev *dev,
			      struct rc_scancode_filter *filter)
{
	u32 mask, s = filter->data;
	enum rc_proto protocol = dev->wakeup_protocol;

	if (protocol >= ARRAY_SIZE(protocols))
		return -EINVAL;

	mask = protocols[protocol].scancode_bits;

	if (!rc_validate_scancode(protocol, s))
		return -EINVAL;

	filter->data &= mask;
	filter->mask &= mask;

	/*
	 * If we have to raw encode the IR for wakeup, we cannot have a mask
	 */
	if (dev->encode_wakeup && filter->mask != 0 && filter->mask != mask)
		return -EINVAL;

	return 0;
}