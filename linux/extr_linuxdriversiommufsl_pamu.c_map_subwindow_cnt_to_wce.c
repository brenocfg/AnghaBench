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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 unsigned int __ffs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int map_subwindow_cnt_to_wce(u32 subwindow_cnt)
{
	/* window count is 2^(WCE+1) bytes */
	return __ffs(subwindow_cnt) - 1;
}