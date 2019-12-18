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
struct snic_io_stats {int /*<<< orphan*/  num_ios; int /*<<< orphan*/  max_active; int /*<<< orphan*/  active; } ;
struct snic_stats {struct snic_io_stats io; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic64_inc (int /*<<< orphan*/ *) ; 
 int atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic64_set (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void
snic_stats_update_active_ios(struct snic_stats *s_stats)
{
	struct snic_io_stats *io = &s_stats->io;
	int nr_active_ios;

	nr_active_ios = atomic64_read(&io->active);
	if (atomic64_read(&io->max_active) < nr_active_ios)
		atomic64_set(&io->max_active, nr_active_ios);

	atomic64_inc(&io->num_ios);
}