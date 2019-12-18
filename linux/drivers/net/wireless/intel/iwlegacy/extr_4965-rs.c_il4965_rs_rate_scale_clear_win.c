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
struct il_rate_scale_data {scalar_t__ stamp; void* average_tpt; scalar_t__ counter; void* success_ratio; scalar_t__ success_counter; scalar_t__ data; } ;

/* Variables and functions */
 void* IL_INVALID_VALUE ; 

__attribute__((used)) static void
il4965_rs_rate_scale_clear_win(struct il_rate_scale_data *win)
{
	win->data = 0;
	win->success_counter = 0;
	win->success_ratio = IL_INVALID_VALUE;
	win->counter = 0;
	win->average_tpt = IL_INVALID_VALUE;
	win->stamp = 0;
}