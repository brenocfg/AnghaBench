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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct devfreq {scalar_t__ previous_freq; int* trans_table; int total_trans; int /*<<< orphan*/ * time_in_state; TYPE_1__* profile; int /*<<< orphan*/  stop_polling; } ;
typedef  int ssize_t ;
struct TYPE_2__ {unsigned int max_state; int* freq_table; } ;

/* Variables and functions */
 scalar_t__ devfreq_update_status (struct devfreq*,scalar_t__) ; 
 int jiffies_to_msecs (int /*<<< orphan*/ ) ; 
 int sprintf (char*,char*,...) ; 
 struct devfreq* to_devfreq (struct device*) ; 

__attribute__((used)) static ssize_t trans_stat_show(struct device *dev,
			       struct device_attribute *attr, char *buf)
{
	struct devfreq *devfreq = to_devfreq(dev);
	ssize_t len;
	int i, j;
	unsigned int max_state = devfreq->profile->max_state;

	if (!devfreq->stop_polling &&
			devfreq_update_status(devfreq, devfreq->previous_freq))
		return 0;
	if (max_state == 0)
		return sprintf(buf, "Not Supported.\n");

	len = sprintf(buf, "     From  :   To\n");
	len += sprintf(buf + len, "           :");
	for (i = 0; i < max_state; i++)
		len += sprintf(buf + len, "%10lu",
				devfreq->profile->freq_table[i]);

	len += sprintf(buf + len, "   time(ms)\n");

	for (i = 0; i < max_state; i++) {
		if (devfreq->profile->freq_table[i]
					== devfreq->previous_freq) {
			len += sprintf(buf + len, "*");
		} else {
			len += sprintf(buf + len, " ");
		}
		len += sprintf(buf + len, "%10lu:",
				devfreq->profile->freq_table[i]);
		for (j = 0; j < max_state; j++)
			len += sprintf(buf + len, "%10u",
				devfreq->trans_table[(i * max_state) + j]);
		len += sprintf(buf + len, "%10u\n",
			jiffies_to_msecs(devfreq->time_in_state[i]));
	}

	len += sprintf(buf + len, "Total transition : %u\n",
					devfreq->total_trans);
	return len;
}