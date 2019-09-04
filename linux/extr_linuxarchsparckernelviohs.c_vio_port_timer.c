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
struct vio_driver_state {int dummy; } ;
struct timer_list {int dummy; } ;

/* Variables and functions */
 struct vio_driver_state* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer ; 
 struct vio_driver_state* vio ; 
 int /*<<< orphan*/  vio_port_up (struct vio_driver_state*) ; 

__attribute__((used)) static void vio_port_timer(struct timer_list *t)
{
	struct vio_driver_state *vio = from_timer(vio, t, timer);

	vio_port_up(vio);
}