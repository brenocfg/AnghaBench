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
struct list_head {int dummy; } ;
struct ocxl_fn {struct list_head afu_list; } ;

/* Variables and functions */

struct list_head *ocxl_function_afu_list(struct ocxl_fn *fn)
{
	return &fn->afu_list;
}