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
typedef  int /*<<< orphan*/  run_fn_t ;

/* Variables and functions */
 int /*<<< orphan*/  iomem_resource ; 
 int /*<<< orphan*/  s3c_pm_run_res (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void s3c_pm_run_sysram(run_fn_t fn, u32 *arg)
{
	s3c_pm_run_res(&iomem_resource, fn, arg);
}