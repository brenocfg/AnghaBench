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
struct device_node {int dummy; } ;
struct devbus_write_params {int sync_enable; int wr_low; int wr_high; int ale_wr; } ;
struct devbus_read_params {int bus_width; int badr_skew; int rd_hold; int acc_next; int rd_setup; int acc_first; int turn_off; } ;
struct devbus {scalar_t__ base; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARMADA_ACC_FIRST_SHIFT ; 
 int ARMADA_ACC_NEXT_SHIFT ; 
 int ARMADA_BADR_SKEW_SHIFT ; 
 int ARMADA_DEV_WIDTH_SHIFT ; 
 int ARMADA_RD_HOLD_SHIFT ; 
 int ARMADA_RD_SETUP_SHIFT ; 
 scalar_t__ ARMADA_READ_PARAM_OFFSET ; 
 int ARMADA_SYNC_ENABLE_SHIFT ; 
 scalar_t__ ARMADA_WRITE_PARAM_OFFSET ; 
 int ARMADA_WR_HIGH_SHIFT ; 
 int ARMADA_WR_LOW_SHIFT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void devbus_armada_set_timing_params(struct devbus *devbus,
					   struct device_node *node,
					   struct devbus_read_params *r,
					   struct devbus_write_params *w)
{
	u32 value;

	/* Set read timings */
	value = r->bus_width << ARMADA_DEV_WIDTH_SHIFT |
		r->badr_skew << ARMADA_BADR_SKEW_SHIFT |
		r->rd_hold   << ARMADA_RD_HOLD_SHIFT   |
		r->acc_next  << ARMADA_ACC_NEXT_SHIFT  |
		r->rd_setup  << ARMADA_RD_SETUP_SHIFT  |
		r->acc_first << ARMADA_ACC_FIRST_SHIFT |
		r->turn_off;

	dev_dbg(devbus->dev, "read parameters register 0x%p = 0x%x\n",
		devbus->base + ARMADA_READ_PARAM_OFFSET,
		value);

	writel(value, devbus->base + ARMADA_READ_PARAM_OFFSET);

	/* Set write timings */
	value = w->sync_enable  << ARMADA_SYNC_ENABLE_SHIFT |
		w->wr_low       << ARMADA_WR_LOW_SHIFT      |
		w->wr_high      << ARMADA_WR_HIGH_SHIFT     |
		w->ale_wr;

	dev_dbg(devbus->dev, "write parameters register: 0x%p = 0x%x\n",
		devbus->base + ARMADA_WRITE_PARAM_OFFSET,
		value);

	writel(value, devbus->base + ARMADA_WRITE_PARAM_OFFSET);
}