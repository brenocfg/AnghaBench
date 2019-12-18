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
struct queue_properties {size_t priority; } ;
struct cik_mqd {size_t cp_hqd_queue_priority; int /*<<< orphan*/  cp_hqd_pipe_priority; } ;

/* Variables and functions */
 int /*<<< orphan*/ * pipe_priority_map ; 

__attribute__((used)) static void set_priority(struct cik_mqd *m, struct queue_properties *q)
{
	m->cp_hqd_pipe_priority = pipe_priority_map[q->priority];
	m->cp_hqd_queue_priority = q->priority;
}