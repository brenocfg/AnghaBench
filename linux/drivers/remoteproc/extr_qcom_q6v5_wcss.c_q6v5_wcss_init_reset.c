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
struct q6v5_wcss {void* wcss_q6_reset; struct device* dev; void* wcss_reset; void* wcss_aon_reset; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 void* devm_reset_control_get (struct device*,char*) ; 

__attribute__((used)) static int q6v5_wcss_init_reset(struct q6v5_wcss *wcss)
{
	struct device *dev = wcss->dev;

	wcss->wcss_aon_reset = devm_reset_control_get(dev, "wcss_aon_reset");
	if (IS_ERR(wcss->wcss_aon_reset)) {
		dev_err(wcss->dev, "unable to acquire wcss_aon_reset\n");
		return PTR_ERR(wcss->wcss_aon_reset);
	}

	wcss->wcss_reset = devm_reset_control_get(dev, "wcss_reset");
	if (IS_ERR(wcss->wcss_reset)) {
		dev_err(wcss->dev, "unable to acquire wcss_reset\n");
		return PTR_ERR(wcss->wcss_reset);
	}

	wcss->wcss_q6_reset = devm_reset_control_get(dev, "wcss_q6_reset");
	if (IS_ERR(wcss->wcss_q6_reset)) {
		dev_err(wcss->dev, "unable to acquire wcss_q6_reset\n");
		return PTR_ERR(wcss->wcss_q6_reset);
	}

	return 0;
}