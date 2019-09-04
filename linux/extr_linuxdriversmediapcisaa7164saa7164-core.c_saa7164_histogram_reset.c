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
struct saa7164_histogram {TYPE_1__* counter1; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int val; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct saa7164_histogram*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void saa7164_histogram_reset(struct saa7164_histogram *hg, char *name)
{
	int i;

	memset(hg, 0, sizeof(struct saa7164_histogram));
	strcpy(hg->name, name);

	/* First 30ms x 1ms */
	for (i = 0; i < 30; i++)
		hg->counter1[0 + i].val = i;

	/* 30 - 200ms x 10ms  */
	for (i = 0; i < 18; i++)
		hg->counter1[30 + i].val = 30 + (i * 10);

	/* 200 - 2000ms x 100ms  */
	for (i = 0; i < 15; i++)
		hg->counter1[48 + i].val = 200 + (i * 200);

	/* Catch all massive value (2secs) */
	hg->counter1[55].val = 2000;

	/* Catch all massive value (4secs) */
	hg->counter1[56].val = 4000;

	/* Catch all massive value (8secs) */
	hg->counter1[57].val = 8000;

	/* Catch all massive value (15secs) */
	hg->counter1[58].val = 15000;

	/* Catch all massive value (30secs) */
	hg->counter1[59].val = 30000;

	/* Catch all massive value (60secs) */
	hg->counter1[60].val = 60000;

	/* Catch all massive value (5mins) */
	hg->counter1[61].val = 300000;

	/* Catch all massive value (15mins) */
	hg->counter1[62].val = 900000;

	/* Catch all massive values (1hr) */
	hg->counter1[63].val = 3600000;
}