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
struct TYPE_2__ {int /*<<< orphan*/  rx_filter; } ;
struct ocelot {TYPE_1__ hwtstamp_config; int /*<<< orphan*/  ptp_clock; int /*<<< orphan*/  dev; int /*<<< orphan*/  ptp_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANA_TABLES_PTP_ID_HIGH ; 
 int /*<<< orphan*/  ANA_TABLES_PTP_ID_LOW ; 
 int /*<<< orphan*/  HWTSTAMP_FILTER_PTP_V2_EVENT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTP_CFG_MISC ; 
 int PTP_CFG_MISC_PTP_EN ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_PTP_CFG ; 
 int SYS_PTP_CFG_PTP_STAMP_WID (int) ; 
 int /*<<< orphan*/  ocelot_ptp_clock_info ; 
 int /*<<< orphan*/  ocelot_write (struct ocelot*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptp_clock_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocelot_init_timestamp(struct ocelot *ocelot)
{
	ocelot->ptp_info = ocelot_ptp_clock_info;
	ocelot->ptp_clock = ptp_clock_register(&ocelot->ptp_info, ocelot->dev);
	if (IS_ERR(ocelot->ptp_clock))
		return PTR_ERR(ocelot->ptp_clock);
	/* Check if PHC support is missing at the configuration level */
	if (!ocelot->ptp_clock)
		return 0;

	ocelot_write(ocelot, SYS_PTP_CFG_PTP_STAMP_WID(30), SYS_PTP_CFG);
	ocelot_write(ocelot, 0xffffffff, ANA_TABLES_PTP_ID_LOW);
	ocelot_write(ocelot, 0xffffffff, ANA_TABLES_PTP_ID_HIGH);

	ocelot_write(ocelot, PTP_CFG_MISC_PTP_EN, PTP_CFG_MISC);

	/* There is no device reconfiguration, PTP Rx stamping is always
	 * enabled.
	 */
	ocelot->hwtstamp_config.rx_filter = HWTSTAMP_FILTER_PTP_V2_EVENT;

	return 0;
}