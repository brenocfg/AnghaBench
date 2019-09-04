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
struct TYPE_2__ {scalar_t__ max_hw_discard_sectors; } ;
struct request_queue {TYPE_1__ limits; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,unsigned long long) ; 

__attribute__((used)) static ssize_t queue_discard_max_hw_show(struct request_queue *q, char *page)
{

	return sprintf(page, "%llu\n",
		(unsigned long long)q->limits.max_hw_discard_sectors << 9);
}