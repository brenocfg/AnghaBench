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
struct loopback_test {scalar_t__ device_count; TYPE_1__* devices; scalar_t__ mask; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int MAX_NUM_DEVICES ; 
 int /*<<< orphan*/  device_enabled (struct loopback_test*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int sanity_check(struct loopback_test *t)
{
	int i;

	if (t->device_count == 0) {
		fprintf(stderr, "No loopback devices found\n");
		return -1;
	}

	for (i = 0; i < MAX_NUM_DEVICES; i++) {
		if (!device_enabled(t, i))
			continue;

		if (t->mask && !strcmp(t->devices[i].name, "")) {
			fprintf(stderr, "Bad device mask %x\n", (1 << i));
			return -1;
		}

	}


	return 0;
}