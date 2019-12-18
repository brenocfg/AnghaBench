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
typedef  int /*<<< orphan*/  u_char ;
struct map_info {int dummy; } ;
struct flchip {scalar_t__ state; int /*<<< orphan*/  mutex; int /*<<< orphan*/  wq; scalar_t__ start; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ FL_READY ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  map_copy_from (struct map_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  otp_enter (struct map_info*,struct flchip*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  otp_exit (struct map_info*,struct flchip*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int do_read_secsi_onechip(struct map_info *map,
					struct flchip *chip, loff_t adr,
					size_t len, u_char *buf,
					size_t grouplen)
{
	DECLARE_WAITQUEUE(wait, current);

 retry:
	mutex_lock(&chip->mutex);

	if (chip->state != FL_READY){
		set_current_state(TASK_UNINTERRUPTIBLE);
		add_wait_queue(&chip->wq, &wait);

		mutex_unlock(&chip->mutex);

		schedule();
		remove_wait_queue(&chip->wq, &wait);

		goto retry;
	}

	adr += chip->start;

	chip->state = FL_READY;

	otp_enter(map, chip, adr, len);
	map_copy_from(map, buf, adr, len);
	otp_exit(map, chip, adr, len);

	wake_up(&chip->wq);
	mutex_unlock(&chip->mutex);

	return 0;
}