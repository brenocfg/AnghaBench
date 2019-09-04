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
struct cpufreq_policy {TYPE_1__* stats; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int total_trans; } ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t show_total_trans(struct cpufreq_policy *policy, char *buf)
{
	return sprintf(buf, "%d\n", policy->stats->total_trans);
}