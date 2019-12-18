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
struct TYPE_2__ {int /*<<< orphan*/  bootstatus; } ;
struct menf21bmc_wdt {TYPE_1__ wdt; int /*<<< orphan*/  i2c_client; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMC_CMD_RST_RSN ; 
 int /*<<< orphan*/  WDIOF_CARDRESET ; 
 int /*<<< orphan*/  WDIOF_EXTERN1 ; 
 int /*<<< orphan*/  WDIOF_EXTERN2 ; 
 int /*<<< orphan*/  WDIOF_POWERUNDER ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int menf21bmc_wdt_set_bootstatus(struct menf21bmc_wdt *data)
{
	int rst_rsn;

	rst_rsn = i2c_smbus_read_byte_data(data->i2c_client, BMC_CMD_RST_RSN);
	if (rst_rsn < 0)
		return rst_rsn;

	if (rst_rsn == 0x02)
		data->wdt.bootstatus |= WDIOF_CARDRESET;
	else if (rst_rsn == 0x05)
		data->wdt.bootstatus |= WDIOF_EXTERN1;
	else if (rst_rsn == 0x06)
		data->wdt.bootstatus |= WDIOF_EXTERN2;
	else if (rst_rsn == 0x0A)
		data->wdt.bootstatus |= WDIOF_POWERUNDER;

	return 0;
}