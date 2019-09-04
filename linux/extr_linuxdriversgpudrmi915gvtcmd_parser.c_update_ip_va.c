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
struct parser_exec_state {unsigned long ring_head; unsigned long ring_tail; scalar_t__ buf_type; unsigned long ring_start; unsigned long ring_size; unsigned long ip_gma; scalar_t__ ret_bb_va; scalar_t__ ip_va; scalar_t__ rb_va; } ;

/* Variables and functions */
 scalar_t__ RING_BUFFER_INSTRUCTION ; 
 scalar_t__ WARN_ON (int) ; 

__attribute__((used)) static inline void update_ip_va(struct parser_exec_state *s)
{
	unsigned long len = 0;

	if (WARN_ON(s->ring_head == s->ring_tail))
		return;

	if (s->buf_type == RING_BUFFER_INSTRUCTION) {
		unsigned long ring_top = s->ring_start + s->ring_size;

		if (s->ring_head > s->ring_tail) {
			if (s->ip_gma >= s->ring_head && s->ip_gma < ring_top)
				len = (s->ip_gma - s->ring_head);
			else if (s->ip_gma >= s->ring_start &&
					s->ip_gma <= s->ring_tail)
				len = (ring_top - s->ring_head) +
					(s->ip_gma - s->ring_start);
		} else
			len = (s->ip_gma - s->ring_head);

		s->ip_va = s->rb_va + len;
	} else {/* shadow batch buffer */
		s->ip_va = s->ret_bb_va;
	}
}