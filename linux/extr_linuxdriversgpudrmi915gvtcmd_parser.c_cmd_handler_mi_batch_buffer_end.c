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
struct parser_exec_state {scalar_t__ buf_type; scalar_t__ ret_ip_gma_bb; scalar_t__ ret_ip_gma_ring; scalar_t__ ring_start; scalar_t__ ring_size; int /*<<< orphan*/  buf_addr_type; int /*<<< orphan*/  saved_buf_addr_type; } ;

/* Variables and functions */
 scalar_t__ BATCH_BUFFER_2ND_LEVEL ; 
 scalar_t__ BATCH_BUFFER_INSTRUCTION ; 
 int /*<<< orphan*/  GTT_BUFFER ; 
 scalar_t__ RING_BUFFER_INSTRUCTION ; 
 int ip_gma_set (struct parser_exec_state*,scalar_t__) ; 

__attribute__((used)) static int cmd_handler_mi_batch_buffer_end(struct parser_exec_state *s)
{
	int ret;

	if (s->buf_type == BATCH_BUFFER_2ND_LEVEL) {
		s->buf_type = BATCH_BUFFER_INSTRUCTION;
		ret = ip_gma_set(s, s->ret_ip_gma_bb);
		s->buf_addr_type = s->saved_buf_addr_type;
	} else {
		s->buf_type = RING_BUFFER_INSTRUCTION;
		s->buf_addr_type = GTT_BUFFER;
		if (s->ret_ip_gma_ring >= s->ring_start + s->ring_size)
			s->ret_ip_gma_ring -= s->ring_size;
		ret = ip_gma_set(s, s->ret_ip_gma_ring);
	}
	return ret;
}