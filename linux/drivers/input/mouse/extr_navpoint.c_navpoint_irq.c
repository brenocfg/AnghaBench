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
typedef  int u32 ;
struct ssp_device {int dummy; } ;
struct navpoint {int* data; int index; int /*<<< orphan*/  dev; struct ssp_device* ssp; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int HEADER_LENGTH (int) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  SSDR ; 
 int /*<<< orphan*/  SSSR ; 
 int SSSR_RNE ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  navpoint_packet (struct navpoint*) ; 
 int pxa_ssp_read_reg (struct ssp_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pxa_ssp_write_reg (struct ssp_device*,int /*<<< orphan*/ ,int) ; 
 int sssr ; 

__attribute__((used)) static irqreturn_t navpoint_irq(int irq, void *dev_id)
{
	struct navpoint *navpoint = dev_id;
	struct ssp_device *ssp = navpoint->ssp;
	irqreturn_t ret = IRQ_NONE;
	u32 status;

	status = pxa_ssp_read_reg(ssp, SSSR);
	if (status & sssr) {
		dev_warn(navpoint->dev,
			 "unexpected interrupt: status=0x%08x\n", status);
		pxa_ssp_write_reg(ssp, SSSR, (status & sssr));
		ret = IRQ_HANDLED;
	}

	while (status & SSSR_RNE) {
		u32 data;

		data = pxa_ssp_read_reg(ssp, SSDR);
		navpoint->data[navpoint->index + 0] = (data >> 8);
		navpoint->data[navpoint->index + 1] = data;
		navpoint->index += 2;
		if (HEADER_LENGTH(navpoint->data[0]) < navpoint->index) {
			navpoint_packet(navpoint);
			navpoint->index = 0;
		}
		status = pxa_ssp_read_reg(ssp, SSSR);
		ret = IRQ_HANDLED;
	}

	return ret;
}