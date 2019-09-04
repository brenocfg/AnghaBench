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
struct task_struct {int dummy; } ;

/* Variables and functions */
 int qcom_boot_secondary (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scss_release_secondary ; 

__attribute__((used)) static int msm8660_boot_secondary(unsigned int cpu, struct task_struct *idle)
{
	return qcom_boot_secondary(cpu, scss_release_secondary);
}