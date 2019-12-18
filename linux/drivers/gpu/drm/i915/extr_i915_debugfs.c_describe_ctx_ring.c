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
struct seq_file {int dummy; } ;
struct intel_ring {int /*<<< orphan*/  emit; int /*<<< orphan*/  tail; int /*<<< orphan*/  head; int /*<<< orphan*/  space; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void describe_ctx_ring(struct seq_file *m, struct intel_ring *ring)
{
	seq_printf(m, " (ringbuffer, space: %d, head: %u, tail: %u, emit: %u)",
		   ring->space, ring->head, ring->tail, ring->emit);
}