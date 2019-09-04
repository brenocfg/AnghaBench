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
typedef  int u8 ;
struct cma3000_platform_data {int mdthr; int mdfftmr; int ffthr; } ;
struct cma3000_accl_data {scalar_t__ g_range; int mode; TYPE_1__* bus_ops; int /*<<< orphan*/  dev; struct cma3000_platform_data* pdata; } ;
struct TYPE_2__ {int ctrl_mod; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMA3000_CTRL ; 
 int /*<<< orphan*/  CMA3000_FFTHR ; 
 int /*<<< orphan*/  CMA3000_MDFFTMR ; 
 int /*<<< orphan*/  CMA3000_MDTHR ; 
 int CMA3000_RANGE2G ; 
 int CMA3000_RANGE8G ; 
 int CMA3000_SET (struct cma3000_accl_data*,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  CMA3000_SETDELAY ; 
 scalar_t__ CMARANGE_2G ; 
 scalar_t__ CMARANGE_8G ; 
 int EIO ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cma3000_poweron(struct cma3000_accl_data *data)
{
	const struct cma3000_platform_data *pdata = data->pdata;
	u8 ctrl = 0;
	int ret;

	if (data->g_range == CMARANGE_2G) {
		ctrl = (data->mode << 1) | CMA3000_RANGE2G;
	} else if (data->g_range == CMARANGE_8G) {
		ctrl = (data->mode << 1) | CMA3000_RANGE8G;
	} else {
		dev_info(data->dev,
			 "Invalid G range specified, assuming 8G\n");
		ctrl = (data->mode << 1) | CMA3000_RANGE8G;
	}

	ctrl |= data->bus_ops->ctrl_mod;

	CMA3000_SET(data, CMA3000_MDTHR, pdata->mdthr,
		    "Motion Detect Threshold");
	CMA3000_SET(data, CMA3000_MDFFTMR, pdata->mdfftmr,
		    "Time register");
	CMA3000_SET(data, CMA3000_FFTHR, pdata->ffthr,
		    "Free fall threshold");
	ret = CMA3000_SET(data, CMA3000_CTRL, ctrl, "Mode setting");
	if (ret < 0)
		return -EIO;

	msleep(CMA3000_SETDELAY);

	return 0;
}