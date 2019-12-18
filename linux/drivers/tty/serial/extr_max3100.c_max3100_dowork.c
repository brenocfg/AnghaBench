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
struct max3100_port {int /*<<< orphan*/  work; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  suspending; int /*<<< orphan*/  force_end_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  freezing (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void max3100_dowork(struct max3100_port *s)
{
	if (!s->force_end_work && !freezing(current) && !s->suspending)
		queue_work(s->workqueue, &s->work);
}