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
struct its_vpe {int /*<<< orphan*/  irq; } ;
struct its_cmd_info {int dummy; } ;

/* Variables and functions */
 int irq_set_vcpu_affinity (int /*<<< orphan*/ ,struct its_cmd_info*) ; 

__attribute__((used)) static int its_send_vpe_cmd(struct its_vpe *vpe, struct its_cmd_info *info)
{
	return irq_set_vcpu_affinity(vpe->irq, info);
}