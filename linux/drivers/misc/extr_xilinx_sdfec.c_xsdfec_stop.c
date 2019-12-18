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
typedef  int /*<<< orphan*/  u32 ;
struct xsdfec_dev {scalar_t__ state; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  XSDFEC_AXIS_ENABLE_ADDR ; 
 int /*<<< orphan*/  XSDFEC_AXIS_IN_ENABLE_MASK ; 
 scalar_t__ XSDFEC_STARTED ; 
 scalar_t__ XSDFEC_STOPPED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xsdfec_regread (struct xsdfec_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsdfec_regwrite (struct xsdfec_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xsdfec_stop(struct xsdfec_dev *xsdfec)
{
	u32 regread;

	if (xsdfec->state != XSDFEC_STARTED)
		dev_dbg(xsdfec->dev, "Device not started correctly");
	/* Disable AXIS_ENABLE Input interfaces only */
	regread = xsdfec_regread(xsdfec, XSDFEC_AXIS_ENABLE_ADDR);
	regread &= (~XSDFEC_AXIS_IN_ENABLE_MASK);
	xsdfec_regwrite(xsdfec, XSDFEC_AXIS_ENABLE_ADDR, regread);
	/* Stop */
	xsdfec->state = XSDFEC_STOPPED;
	return 0;
}