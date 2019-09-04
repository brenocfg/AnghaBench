#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct work_struct {int dummy; } ;
struct stp_sstpi {int dummy; } ;
struct clock_sync_data {int /*<<< orphan*/  cpus; } ;
typedef  int /*<<< orphan*/  stp_sync ;
struct TYPE_3__ {scalar_t__ c; } ;

/* Variables and functions */
 scalar_t__ HZ ; 
 int /*<<< orphan*/  STP_OP_CTRL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ check_sync_clock () ; 
 int chsc_sstpc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int chsc_sstpi (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 int /*<<< orphan*/  cpus_read_lock () ; 
 int /*<<< orphan*/  cpus_read_unlock () ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  memset (struct clock_sync_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ num_online_cpus () ; 
 int /*<<< orphan*/  stop_machine_cpuslocked (int /*<<< orphan*/ ,struct clock_sync_data*,int /*<<< orphan*/ ) ; 
 TYPE_1__ stp_info ; 
 int /*<<< orphan*/  stp_online ; 
 int /*<<< orphan*/  stp_page ; 
 int /*<<< orphan*/  stp_sync_clock ; 
 int /*<<< orphan*/  stp_timer ; 
 int /*<<< orphan*/  stp_work_mutex ; 

__attribute__((used)) static void stp_work_fn(struct work_struct *work)
{
	struct clock_sync_data stp_sync;
	int rc;

	/* prevent multiple execution. */
	mutex_lock(&stp_work_mutex);

	if (!stp_online) {
		chsc_sstpc(stp_page, STP_OP_CTRL, 0x0000, NULL);
		del_timer_sync(&stp_timer);
		goto out_unlock;
	}

	rc = chsc_sstpc(stp_page, STP_OP_CTRL, 0xb0e0, NULL);
	if (rc)
		goto out_unlock;

	rc = chsc_sstpi(stp_page, &stp_info, sizeof(struct stp_sstpi));
	if (rc || stp_info.c == 0)
		goto out_unlock;

	/* Skip synchronization if the clock is already in sync. */
	if (check_sync_clock())
		goto out_unlock;

	memset(&stp_sync, 0, sizeof(stp_sync));
	cpus_read_lock();
	atomic_set(&stp_sync.cpus, num_online_cpus() - 1);
	stop_machine_cpuslocked(stp_sync_clock, &stp_sync, cpu_online_mask);
	cpus_read_unlock();

	if (!check_sync_clock())
		/*
		 * There is a usable clock but the synchonization failed.
		 * Retry after a second.
		 */
		mod_timer(&stp_timer, jiffies + HZ);

out_unlock:
	mutex_unlock(&stp_work_mutex);
}