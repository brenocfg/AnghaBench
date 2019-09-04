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
struct bop_ring_buffer {int /*<<< orphan*/  bops; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned brb_next(struct bop_ring_buffer *brb, unsigned old)
{
	unsigned r = old + 1;
	return r >= ARRAY_SIZE(brb->bops) ? 0 : r;
}