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
typedef  size_t u32 ;
struct dsaf_device {TYPE_1__** mac_cb; } ;
struct TYPE_2__ {size_t port_rst_off; } ;

/* Variables and functions */
 size_t DSAF_SUB_SC_PPE_RESET_DREQ_REG ; 
 size_t DSAF_SUB_SC_PPE_RESET_REQ_REG ; 
 size_t RESET_REQ_OR_DREQ ; 
 int /*<<< orphan*/  dsaf_write_sub (struct dsaf_device*,size_t,size_t) ; 

__attribute__((used)) static void hns_ppe_srst_by_port(struct dsaf_device *dsaf_dev, u32 port,
				 bool dereset)
{
	u32 reg_val = 0;
	u32 reg_addr;

	reg_val |= RESET_REQ_OR_DREQ <<	dsaf_dev->mac_cb[port]->port_rst_off;

	if (!dereset)
		reg_addr = DSAF_SUB_SC_PPE_RESET_REQ_REG;
	else
		reg_addr = DSAF_SUB_SC_PPE_RESET_DREQ_REG;

	dsaf_write_sub(dsaf_dev, reg_addr, reg_val);
}