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
struct bop_ring_buffer {int /*<<< orphan*/  begin; } ;

/* Variables and functions */
 int ENODATA ; 
 scalar_t__ brb_empty (struct bop_ring_buffer*) ; 
 int /*<<< orphan*/  brb_next (struct bop_ring_buffer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int brb_pop(struct bop_ring_buffer *brb)
{
	if (brb_empty(brb))
		return -ENODATA;

	brb->begin = brb_next(brb, brb->begin);

	return 0;
}