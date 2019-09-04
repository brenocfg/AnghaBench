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
struct pt_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct pt_buffer*) ; 
 int /*<<< orphan*/  pt_buffer_fini_topa (struct pt_buffer*) ; 

__attribute__((used)) static void pt_buffer_free_aux(void *data)
{
	struct pt_buffer *buf = data;

	pt_buffer_fini_topa(buf);
	kfree(buf);
}