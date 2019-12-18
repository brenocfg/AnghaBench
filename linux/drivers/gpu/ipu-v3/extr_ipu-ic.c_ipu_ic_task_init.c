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
struct ipu_ic_csc {int dummy; } ;
struct ipu_ic {int dummy; } ;

/* Variables and functions */
 int ipu_ic_task_init_rsc (struct ipu_ic*,struct ipu_ic_csc const*,int,int,int,int,int /*<<< orphan*/ ) ; 

int ipu_ic_task_init(struct ipu_ic *ic,
		     const struct ipu_ic_csc *csc,
		     int in_width, int in_height,
		     int out_width, int out_height)
{
	return ipu_ic_task_init_rsc(ic, csc,
				    in_width, in_height,
				    out_width, out_height, 0);
}