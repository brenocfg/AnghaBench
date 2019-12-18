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
struct work_struct {int dummy; } ;

/* Variables and functions */
 int DM_BUFIO_WORK_TIMER_SECS ; 
 int HZ ; 
 int /*<<< orphan*/  cleanup_old_buffers () ; 
 int /*<<< orphan*/  dm_bufio_cleanup_old_work ; 
 int /*<<< orphan*/  dm_bufio_wq ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void work_fn(struct work_struct *w)
{
	cleanup_old_buffers();

	queue_delayed_work(dm_bufio_wq, &dm_bufio_cleanup_old_work,
			   DM_BUFIO_WORK_TIMER_SECS * HZ);
}