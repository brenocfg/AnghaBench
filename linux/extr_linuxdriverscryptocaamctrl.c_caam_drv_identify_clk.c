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
struct clk {int dummy; } ;

/* Variables and functions */
 scalar_t__ caam_imx ; 
 struct clk* devm_clk_get (struct device*,char*) ; 

__attribute__((used)) static inline struct clk *caam_drv_identify_clk(struct device *dev,
						char *clk_name)
{
	return caam_imx ? devm_clk_get(dev, clk_name) : NULL;
}