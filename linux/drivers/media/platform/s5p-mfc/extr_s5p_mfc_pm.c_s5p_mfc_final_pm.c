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
struct s5p_mfc_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 TYPE_1__* pm ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 

void s5p_mfc_final_pm(struct s5p_mfc_dev *dev)
{
	pm_runtime_disable(pm->device);
}