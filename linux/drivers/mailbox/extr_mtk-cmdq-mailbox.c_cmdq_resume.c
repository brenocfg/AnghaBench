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
struct device {int dummy; } ;
struct cmdq {int suspended; int /*<<< orphan*/  clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ clk_prepare (int /*<<< orphan*/ ) ; 
 struct cmdq* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static int cmdq_resume(struct device *dev)
{
	struct cmdq *cmdq = dev_get_drvdata(dev);

	WARN_ON(clk_prepare(cmdq->clock) < 0);
	cmdq->suspended = false;
	return 0;
}