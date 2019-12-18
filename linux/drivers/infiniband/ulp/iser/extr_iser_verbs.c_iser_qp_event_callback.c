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
struct ib_event {int /*<<< orphan*/  event; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_event_msg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iser_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iser_qp_event_callback(struct ib_event *cause, void *context)
{
	iser_err("qp event %s (%d)\n",
		 ib_event_msg(cause->event), cause->event);
}