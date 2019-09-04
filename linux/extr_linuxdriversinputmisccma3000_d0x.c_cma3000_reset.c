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
struct cma3000_accl_data {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CMA3000_READ (struct cma3000_accl_data*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CMA3000_RSTR ; 
 int /*<<< orphan*/  CMA3000_SET (struct cma3000_accl_data*,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  CMA3000_STATUS ; 
 int CMA3000_STATUS_PERR ; 
 int EIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static int cma3000_reset(struct cma3000_accl_data *data)
{
	int val;

	/* Reset sequence */
	CMA3000_SET(data, CMA3000_RSTR, 0x02, "Reset");
	CMA3000_SET(data, CMA3000_RSTR, 0x0A, "Reset");
	CMA3000_SET(data, CMA3000_RSTR, 0x04, "Reset");

	/* Settling time delay */
	mdelay(10);

	val = CMA3000_READ(data, CMA3000_STATUS, "Status");
	if (val < 0) {
		dev_err(data->dev, "Reset failed\n");
		return val;
	}

	if (val & CMA3000_STATUS_PERR) {
		dev_err(data->dev, "Parity Error\n");
		return -EIO;
	}

	return 0;
}