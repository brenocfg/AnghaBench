#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  tx_kicks; } ;
struct vector_private {int /*<<< orphan*/  tx_queue; TYPE_1__ estats; } ;
struct timer_list {int dummy; } ;

/* Variables and functions */
 struct vector_private* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tl ; 
 int /*<<< orphan*/  vector_send (int /*<<< orphan*/ ) ; 
 struct vector_private* vp ; 

__attribute__((used)) static void vector_timer_expire(struct timer_list *t)
{
	struct vector_private *vp = from_timer(vp, t, tl);

	vp->estats.tx_kicks++;
	vector_send(vp->tx_queue);
}