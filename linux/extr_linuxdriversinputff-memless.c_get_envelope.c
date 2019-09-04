#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ff_envelope {int dummy; } ;
struct TYPE_5__ {struct ff_envelope const envelope; } ;
struct TYPE_4__ {struct ff_envelope const envelope; } ;
struct TYPE_6__ {TYPE_2__ constant; TYPE_1__ periodic; } ;
struct ff_effect {int type; TYPE_3__ u; } ;

/* Variables and functions */
#define  FF_CONSTANT 129 
#define  FF_PERIODIC 128 

__attribute__((used)) static const struct ff_envelope *get_envelope(const struct ff_effect *effect)
{
	static const struct ff_envelope empty_envelope;

	switch (effect->type) {
	case FF_PERIODIC:
		return &effect->u.periodic.envelope;

	case FF_CONSTANT:
		return &effect->u.constant.envelope;

	default:
		return &empty_envelope;
	}
}