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

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_unregister_template (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcm_qla2xxx_free_wq ; 
 int /*<<< orphan*/  tcm_qla2xxx_npiv_ops ; 
 int /*<<< orphan*/  tcm_qla2xxx_ops ; 

__attribute__((used)) static void tcm_qla2xxx_deregister_configfs(void)
{
	destroy_workqueue(tcm_qla2xxx_free_wq);

	target_unregister_template(&tcm_qla2xxx_ops);
	target_unregister_template(&tcm_qla2xxx_npiv_ops);
}