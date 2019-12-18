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
typedef  int /*<<< orphan*/  time_t ;
struct tm {int dummy; } ;
struct loopback_test {char* test_name; int size; int iteration_max; int device_count; int /*<<< orphan*/  porcelain; scalar_t__ file_output; int /*<<< orphan*/  aggregate_results; scalar_t__ aggregate_output; TYPE_1__* devices; } ;
typedef  int /*<<< orphan*/  file_name ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_2__ {char* name; int /*<<< orphan*/  results; } ;

/* Variables and functions */
 int CSV_MAX_LINE ; 
 int MAX_SYSFS_PATH ; 
 int O_APPEND ; 
 int O_CREAT ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  device_enabled (struct loopback_test*,int) ; 
 int format_output (struct loopback_test*,int /*<<< orphan*/ *,char*,char*,int,struct tm*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 struct tm* localtime (int /*<<< orphan*/ *) ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int write (int,char*,int) ; 

__attribute__((used)) static int log_results(struct loopback_test *t)
{
	int fd, i, len, ret;
	struct tm tm;
	time_t local_time;
	char file_name[MAX_SYSFS_PATH];
	char data[CSV_MAX_LINE];

	local_time = time(NULL);
	tm = *localtime(&local_time);

	/*
	 * file name will test_name_size_iteration_max.csv
	 * every time the same test with the same parameters is run we will then
	 * append to the same CSV with datestamp - representing each test
	 * dataset.
	 */
	if (t->file_output && !t->porcelain) {
		snprintf(file_name, sizeof(file_name), "%s_%d_%d.csv",
			 t->test_name, t->size, t->iteration_max);

		fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0) {
			fprintf(stderr, "unable to open %s for appendation\n", file_name);
			abort();
		}

	}
	for (i = 0; i < t->device_count; i++) {
		if (!device_enabled(t, i))
			continue;

		len = format_output(t, &t->devices[i].results,
				    t->devices[i].name,
				    data, sizeof(data), &tm);
		if (t->file_output && !t->porcelain) {
			ret = write(fd, data, len);
			if (ret == -1)
				fprintf(stderr, "unable to write %d bytes to csv.\n", len);
		}

	}


	if (t->aggregate_output) {
		len = format_output(t, &t->aggregate_results, "aggregate",
				    data, sizeof(data), &tm);
		if (t->file_output && !t->porcelain) {
			ret = write(fd, data, len);
			if (ret == -1)
				fprintf(stderr, "unable to write %d bytes to csv.\n", len);
		}
	}

	if (t->file_output && !t->porcelain)
		close(fd);

	return 0;
}