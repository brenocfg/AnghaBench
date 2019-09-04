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
struct dc_sink {int /*<<< orphan*/ * dc_container_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void destruct(struct dc_sink *sink)
{
	if (sink->dc_container_id) {
		kfree(sink->dc_container_id);
		sink->dc_container_id = NULL;
	}
}