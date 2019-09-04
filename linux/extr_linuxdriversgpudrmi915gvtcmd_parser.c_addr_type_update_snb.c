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
struct parser_exec_state {scalar_t__ buf_type; int /*<<< orphan*/  buf_addr_type; } ;

/* Variables and functions */
 int BATCH_BUFFER_ADR_SPACE_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PPGTT_BUFFER ; 
 scalar_t__ RING_BUFFER_INSTRUCTION ; 
 int /*<<< orphan*/  cmd_val (struct parser_exec_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void addr_type_update_snb(struct parser_exec_state *s)
{
	if ((s->buf_type == RING_BUFFER_INSTRUCTION) &&
			(BATCH_BUFFER_ADR_SPACE_BIT(cmd_val(s, 0)) == 1)) {
		s->buf_addr_type = PPGTT_BUFFER;
	}
}