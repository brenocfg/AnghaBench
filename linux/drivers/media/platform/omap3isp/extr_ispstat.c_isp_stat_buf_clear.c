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
struct ispstat {TYPE_1__* buf; } ;
struct TYPE_2__ {int empty; } ;

/* Variables and functions */
 int STAT_MAX_BUFS ; 

__attribute__((used)) static void isp_stat_buf_clear(struct ispstat *stat)
{
	int i;

	for (i = 0; i < STAT_MAX_BUFS; i++)
		stat->buf[i].empty = 1;
}