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
struct isp_res_device {int dummy; } ;
struct isp_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNT ; 
 int /*<<< orphan*/  IN_SIZE ; 
 int /*<<< orphan*/  IN_START ; 
 int /*<<< orphan*/  OUT_SIZE ; 
 int /*<<< orphan*/  PCR ; 
 int /*<<< orphan*/  RSZ_PRINT_REGISTER (struct isp_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDR_INADD ; 
 int /*<<< orphan*/  SDR_INOFF ; 
 int /*<<< orphan*/  SDR_OUTADD ; 
 int /*<<< orphan*/  SDR_OUTOFF ; 
 int /*<<< orphan*/  YENH ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 struct isp_device* to_isp_device (struct isp_res_device*) ; 

__attribute__((used)) static void resizer_print_status(struct isp_res_device *res)
{
	struct isp_device *isp = to_isp_device(res);

	dev_dbg(isp->dev, "-------------Resizer Register dump----------\n");

	RSZ_PRINT_REGISTER(isp, PCR);
	RSZ_PRINT_REGISTER(isp, CNT);
	RSZ_PRINT_REGISTER(isp, OUT_SIZE);
	RSZ_PRINT_REGISTER(isp, IN_START);
	RSZ_PRINT_REGISTER(isp, IN_SIZE);
	RSZ_PRINT_REGISTER(isp, SDR_INADD);
	RSZ_PRINT_REGISTER(isp, SDR_INOFF);
	RSZ_PRINT_REGISTER(isp, SDR_OUTADD);
	RSZ_PRINT_REGISTER(isp, SDR_OUTOFF);
	RSZ_PRINT_REGISTER(isp, YENH);

	dev_dbg(isp->dev, "--------------------------------------------\n");
}