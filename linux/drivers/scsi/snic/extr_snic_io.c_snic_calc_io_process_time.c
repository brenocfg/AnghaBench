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
typedef  scalar_t__ u64 ;
struct snic_req_info {scalar_t__ start_time; } ;
struct TYPE_3__ {int /*<<< orphan*/  max_time; } ;
struct TYPE_4__ {TYPE_1__ io; } ;
struct snic {TYPE_2__ s_stats; } ;

/* Variables and functions */
 scalar_t__ atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic64_set (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ jiffies ; 

void
snic_calc_io_process_time(struct snic *snic, struct snic_req_info *rqi)
{
	u64 duration;

	duration = jiffies - rqi->start_time;

	if (duration > atomic64_read(&snic->s_stats.io.max_time))
		atomic64_set(&snic->s_stats.io.max_time, duration);
}