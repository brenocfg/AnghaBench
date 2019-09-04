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
struct fw_cdev_get_cycle_timer {int local_time; int /*<<< orphan*/  cycle_timer; } ;
union ioctl_arg {struct fw_cdev_get_cycle_timer get_cycle_timer; } ;
struct fw_cdev_get_cycle_timer2 {int tv_sec; int tv_nsec; int /*<<< orphan*/  cycle_timer; int /*<<< orphan*/  clk_id; } ;
struct client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int NSEC_PER_USEC ; 
 int USEC_PER_SEC ; 
 int /*<<< orphan*/  ioctl_get_cycle_timer2 (struct client*,union ioctl_arg*) ; 

__attribute__((used)) static int ioctl_get_cycle_timer(struct client *client, union ioctl_arg *arg)
{
	struct fw_cdev_get_cycle_timer *a = &arg->get_cycle_timer;
	struct fw_cdev_get_cycle_timer2 ct2;

	ct2.clk_id = CLOCK_REALTIME;
	ioctl_get_cycle_timer2(client, (union ioctl_arg *)&ct2);

	a->local_time = ct2.tv_sec * USEC_PER_SEC + ct2.tv_nsec / NSEC_PER_USEC;
	a->cycle_timer = ct2.cycle_timer;

	return 0;
}