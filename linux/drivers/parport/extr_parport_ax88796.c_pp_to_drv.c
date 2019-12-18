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
struct parport {struct ax_drvdata* private_data; } ;
struct ax_drvdata {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct ax_drvdata *pp_to_drv(struct parport *p)
{
	return p->private_data;
}