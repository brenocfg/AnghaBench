#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fotg210_hcd {scalar_t__ async_unlink; TYPE_2__* async; scalar_t__ async_count; } ;
struct TYPE_3__ {scalar_t__ qh; } ;
struct TYPE_4__ {TYPE_1__ qh_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  fotg210_poll_ASS (struct fotg210_hcd*) ; 

__attribute__((used)) static void disable_async(struct fotg210_hcd *fotg210)
{
	if (--fotg210->async_count)
		return;

	/* The async schedule and async_unlink list are supposed to be empty */
	WARN_ON(fotg210->async->qh_next.qh || fotg210->async_unlink);

	/* Don't turn off the schedule until ASS is 1 */
	fotg210_poll_ASS(fotg210);
}