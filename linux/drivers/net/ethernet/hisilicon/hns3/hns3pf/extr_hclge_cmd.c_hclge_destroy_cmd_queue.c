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
struct hclge_hw {TYPE_1__ cmq; } ;

/* Variables and functions */
 int /*<<< orphan*/  hclge_destroy_queue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hclge_destroy_cmd_queue(struct hclge_hw *hw)
{
	hclge_destroy_queue(&hw->cmq.csq);
	hclge_destroy_queue(&hw->cmq.crq);
}