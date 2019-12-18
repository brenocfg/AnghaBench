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
struct pattern_trig_data {int npatterns; int is_hw_pattern; int /*<<< orphan*/  lock; TYPE_1__* patterns; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  delta_t; int /*<<< orphan*/  brightness; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ scnprintf (char*,scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t pattern_trig_show_patterns(struct pattern_trig_data *data,
					  char *buf, bool hw_pattern)
{
	ssize_t count = 0;
	int i;

	mutex_lock(&data->lock);

	if (!data->npatterns || (data->is_hw_pattern ^ hw_pattern))
		goto out;

	for (i = 0; i < data->npatterns; i++) {
		count += scnprintf(buf + count, PAGE_SIZE - count,
				   "%d %u ",
				   data->patterns[i].brightness,
				   data->patterns[i].delta_t);
	}

	buf[count - 1] = '\n';

out:
	mutex_unlock(&data->lock);
	return count;
}