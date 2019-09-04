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
struct iowait {scalar_t__ starved_cnt; } ;

/* Variables and functions */

__attribute__((used)) static inline void iowait_starve_clear(bool pkts_sent, struct iowait *w)
{
	if (pkts_sent)
		w->starved_cnt = 0;
}