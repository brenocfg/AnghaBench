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
typedef  int u32 ;
struct csid_device {int /*<<< orphan*/  reset_complete; scalar_t__ base; TYPE_1__* camss; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  enum camss_version { ____Placeholder_camss_version } camss_version ;
struct TYPE_2__ {int version; } ;

/* Variables and functions */
 scalar_t__ CAMSS_CSID_IRQ_CLEAR_CMD (int) ; 
 scalar_t__ CAMSS_CSID_IRQ_STATUS (int) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t csid_isr(int irq, void *dev)
{
	struct csid_device *csid = dev;
	enum camss_version ver = csid->camss->version;
	u32 value;

	value = readl_relaxed(csid->base + CAMSS_CSID_IRQ_STATUS(ver));
	writel_relaxed(value, csid->base + CAMSS_CSID_IRQ_CLEAR_CMD(ver));

	if ((value >> 11) & 0x1)
		complete(&csid->reset_complete);

	return IRQ_HANDLED;
}