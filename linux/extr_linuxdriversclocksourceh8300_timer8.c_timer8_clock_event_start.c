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
struct timer8_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  timer8_set_next (struct timer8_priv*,unsigned long) ; 
 int /*<<< orphan*/  timer8_start (struct timer8_priv*) ; 

__attribute__((used)) static void timer8_clock_event_start(struct timer8_priv *p, unsigned long delta)
{
	timer8_start(p);
	timer8_set_next(p, delta);
}