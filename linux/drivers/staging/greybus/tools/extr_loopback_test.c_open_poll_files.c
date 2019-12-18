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
struct loopback_test {int device_count; int poll_count; TYPE_1__* fds; struct loopback_device* devices; } ;
struct loopback_device {char* sysfs_entry; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {scalar_t__ fd; int events; scalar_t__ revents; } ;

/* Variables and functions */
 int EPOLLERR ; 
 int EPOLLPRI ; 
 int MAX_STR_LEN ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  device_enabled (struct loopback_test*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int open_poll_files(struct loopback_test *t)
{
	struct loopback_device *dev;
	char buf[MAX_STR_LEN];
	char dummy;
	int fds_idx = 0;
	int i;

	for (i = 0; i < t->device_count; i++) {
		dev = &t->devices[i];

		if (!device_enabled(t, i))
			continue;

		snprintf(buf, sizeof(buf), "%s%s", dev->sysfs_entry, "iteration_count");
		t->fds[fds_idx].fd = open(buf, O_RDONLY);
		if (t->fds[fds_idx].fd < 0) {
			fprintf(stderr, "Error opening poll file!\n");
			goto err;
		}
		read(t->fds[fds_idx].fd, &dummy, 1);
		t->fds[fds_idx].events = EPOLLERR|EPOLLPRI;
		t->fds[fds_idx].revents = 0;
		fds_idx++;
	}

	t->poll_count = fds_idx;

	return 0;

err:
	for (i = 0; i < fds_idx; i++)
		close(t->fds[i].fd);

	return -1;
}