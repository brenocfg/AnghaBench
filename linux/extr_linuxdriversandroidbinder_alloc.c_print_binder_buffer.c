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
struct binder_buffer {scalar_t__ transaction; int /*<<< orphan*/  extra_buffers_size; int /*<<< orphan*/  offsets_size; int /*<<< orphan*/  data_size; int /*<<< orphan*/  data; int /*<<< orphan*/  debug_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void print_binder_buffer(struct seq_file *m, const char *prefix,
				struct binder_buffer *buffer)
{
	seq_printf(m, "%s %d: %pK size %zd:%zd:%zd %s\n",
		   prefix, buffer->debug_id, buffer->data,
		   buffer->data_size, buffer->offsets_size,
		   buffer->extra_buffers_size,
		   buffer->transaction ? "active" : "delivered");
}