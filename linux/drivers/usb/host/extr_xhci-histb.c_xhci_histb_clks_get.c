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
struct xhci_hcd_histb {void* suspend_clk; void* pipe_clk; void* utmi_clk; void* bus_clk; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 void* devm_clk_get (struct device*,char*) ; 

__attribute__((used)) static int xhci_histb_clks_get(struct xhci_hcd_histb *histb)
{
	struct device *dev = histb->dev;

	histb->bus_clk = devm_clk_get(dev, "bus");
	if (IS_ERR(histb->bus_clk)) {
		dev_err(dev, "fail to get bus clk\n");
		return PTR_ERR(histb->bus_clk);
	}

	histb->utmi_clk = devm_clk_get(dev, "utmi");
	if (IS_ERR(histb->utmi_clk)) {
		dev_err(dev, "fail to get utmi clk\n");
		return PTR_ERR(histb->utmi_clk);
	}

	histb->pipe_clk = devm_clk_get(dev, "pipe");
	if (IS_ERR(histb->pipe_clk)) {
		dev_err(dev, "fail to get pipe clk\n");
		return PTR_ERR(histb->pipe_clk);
	}

	histb->suspend_clk = devm_clk_get(dev, "suspend");
	if (IS_ERR(histb->suspend_clk)) {
		dev_err(dev, "fail to get suspend clk\n");
		return PTR_ERR(histb->suspend_clk);
	}

	return 0;
}