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
struct m_can_classdev {int /*<<< orphan*/  dev; void* cclk; void* hclk; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 void* devm_clk_get (int /*<<< orphan*/ ,char*) ; 

int m_can_class_get_clocks(struct m_can_classdev *m_can_dev)
{
	int ret = 0;

	m_can_dev->hclk = devm_clk_get(m_can_dev->dev, "hclk");
	m_can_dev->cclk = devm_clk_get(m_can_dev->dev, "cclk");

	if (IS_ERR(m_can_dev->cclk)) {
		dev_err(m_can_dev->dev, "no clock found\n");
		ret = -ENODEV;
	}

	return ret;
}