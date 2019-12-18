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
struct seq_file {int dummy; } ;
struct dasd_profile_info {int dasd_io_reqs; int /*<<< orphan*/  dasd_io_nr_req; int /*<<< orphan*/  dasd_io_time3; int /*<<< orphan*/  dasd_io_time2ps; int /*<<< orphan*/  dasd_io_time2; int /*<<< orphan*/  dasd_io_time1; int /*<<< orphan*/  dasd_io_timps; int /*<<< orphan*/  dasd_io_times; int /*<<< orphan*/  dasd_io_secs; int /*<<< orphan*/  dasd_io_sects; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; struct dasd_profile_info* data; } ;

/* Variables and functions */
 TYPE_1__ dasd_global_profile ; 
 int /*<<< orphan*/  dasd_statistics_array (struct seq_file*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dasd_stats_proc_show(struct seq_file *m, void *v)
{
#ifdef CONFIG_DASD_PROFILE
	struct dasd_profile_info *prof;
	int factor;

	spin_lock_bh(&dasd_global_profile.lock);
	prof = dasd_global_profile.data;
	if (!prof) {
		spin_unlock_bh(&dasd_global_profile.lock);
		seq_printf(m, "Statistics are off - they might be "
				    "switched on using 'echo set on > "
				    "/proc/dasd/statistics'\n");
		return 0;
	}

	/* prevent counter 'overflow' on output */
	for (factor = 1; (prof->dasd_io_reqs / factor) > 9999999;
	     factor *= 10);

	seq_printf(m, "%d dasd I/O requests\n", prof->dasd_io_reqs);
	seq_printf(m, "with %u sectors(512B each)\n",
		       prof->dasd_io_sects);
	seq_printf(m, "Scale Factor is  %d\n", factor);
	seq_printf(m,
		       "   __<4	   ___8	   __16	   __32	   __64	   _128	"
		       "   _256	   _512	   __1k	   __2k	   __4k	   __8k	"
		       "   _16k	   _32k	   _64k	   128k\n");
	seq_printf(m,
		       "   _256	   _512	   __1M	   __2M	   __4M	   __8M	"
		       "   _16M	   _32M	   _64M	   128M	   256M	   512M	"
		       "   __1G	   __2G	   __4G " "   _>4G\n");

	seq_printf(m, "Histogram of sizes (512B secs)\n");
	dasd_statistics_array(m, prof->dasd_io_secs, factor);
	seq_printf(m, "Histogram of I/O times (microseconds)\n");
	dasd_statistics_array(m, prof->dasd_io_times, factor);
	seq_printf(m, "Histogram of I/O times per sector\n");
	dasd_statistics_array(m, prof->dasd_io_timps, factor);
	seq_printf(m, "Histogram of I/O time till ssch\n");
	dasd_statistics_array(m, prof->dasd_io_time1, factor);
	seq_printf(m, "Histogram of I/O time between ssch and irq\n");
	dasd_statistics_array(m, prof->dasd_io_time2, factor);
	seq_printf(m, "Histogram of I/O time between ssch "
			    "and irq per sector\n");
	dasd_statistics_array(m, prof->dasd_io_time2ps, factor);
	seq_printf(m, "Histogram of I/O time between irq and end\n");
	dasd_statistics_array(m, prof->dasd_io_time3, factor);
	seq_printf(m, "# of req in chanq at enqueuing (1..32) \n");
	dasd_statistics_array(m, prof->dasd_io_nr_req, factor);
	spin_unlock_bh(&dasd_global_profile.lock);
#else
	seq_printf(m, "Statistics are not activated in this kernel\n");
#endif
	return 0;
}