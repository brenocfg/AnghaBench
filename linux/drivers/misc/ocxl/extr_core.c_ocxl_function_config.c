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
struct ocxl_fn_config {int dummy; } ;
struct ocxl_fn {struct ocxl_fn_config const config; } ;

/* Variables and functions */

const struct ocxl_fn_config *ocxl_function_config(struct ocxl_fn *fn)
{
	return &fn->config;
}