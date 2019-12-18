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
struct TYPE_3__ {scalar_t__ addr; } ;
struct TYPE_4__ {TYPE_1__ buf; } ;
struct ef4_channel {unsigned int eventq_mask; TYPE_2__ eventq; } ;
typedef  int /*<<< orphan*/  ef4_qword_t ;

/* Variables and functions */

__attribute__((used)) static inline ef4_qword_t *ef4_event(struct ef4_channel *channel,
				     unsigned int index)
{
	return ((ef4_qword_t *) (channel->eventq.buf.addr)) +
		(index & channel->eventq_mask);
}