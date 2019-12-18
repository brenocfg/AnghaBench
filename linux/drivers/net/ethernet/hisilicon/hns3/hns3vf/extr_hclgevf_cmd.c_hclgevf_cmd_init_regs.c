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
struct TYPE_2__ {int /*<<< orphan*/  crq; int /*<<< orphan*/  csq; } ;
struct hclgevf_hw {TYPE_1__ cmq; } ;

/* Variables and functions */
 int /*<<< orphan*/  hclgevf_cmd_config_regs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hclgevf_cmd_init_regs(struct hclgevf_hw *hw)
{
	hclgevf_cmd_config_regs(&hw->cmq.csq);
	hclgevf_cmd_config_regs(&hw->cmq.crq);
}