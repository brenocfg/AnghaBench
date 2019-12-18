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
struct c67x00_device {int dummy; } ;

/* Variables and functions */
 int C67X00_SIES ; 
 int /*<<< orphan*/  HPI_IRQ_ROUTING_REG ; 
 int /*<<< orphan*/  SIEMSG_REG (int) ; 
 int /*<<< orphan*/  c67x00_ll_hpi_status (struct c67x00_device*) ; 
 int /*<<< orphan*/  hpi_read_word (struct c67x00_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpi_recv_mbox (struct c67x00_device*) ; 
 int /*<<< orphan*/  hpi_write_word (struct c67x00_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void c67x00_ll_hpi_reg_init(struct c67x00_device *dev)
{
	int i;

	hpi_recv_mbox(dev);
	c67x00_ll_hpi_status(dev);
	hpi_write_word(dev, HPI_IRQ_ROUTING_REG, 0);

	for (i = 0; i < C67X00_SIES; i++) {
		hpi_write_word(dev, SIEMSG_REG(i), 0);
		hpi_read_word(dev, SIEMSG_REG(i));
	}
}