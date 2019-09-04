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
struct timer_list {int dummy; } ;
typedef  int /*<<< orphan*/  isdnloop_card ;

/* Variables and functions */
 int /*<<< orphan*/ * c_timer ; 
 int /*<<< orphan*/ * card ; 
 int /*<<< orphan*/ * from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isdnloop_atimeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
isdnloop_atimeout0(struct timer_list *t)
{
	isdnloop_card *card = from_timer(card, t, c_timer[0]);

	isdnloop_atimeout(card, 0);
}