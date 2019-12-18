#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ SINK_SELF_REFRESH_STATUS; } ;
union psr_sink_psr_status {unsigned char raw; TYPE_3__ bits; } ;
struct TYPE_5__ {scalar_t__ RFB_STORAGE_ERROR; scalar_t__ LINK_CRC_ERROR; } ;
union psr_error_status {unsigned char raw; TYPE_2__ bits; } ;
struct TYPE_4__ {scalar_t__ ENABLE; } ;
union dpcd_psr_configuration {unsigned char raw; TYPE_1__ bits; } ;
struct dc_link {int /*<<< orphan*/  ctx; int /*<<< orphan*/  psr_enabled; } ;
typedef  int /*<<< orphan*/  dpcdbuf ;

/* Variables and functions */
 scalar_t__ PSR_SINK_STATE_ACTIVE_DISPLAY_FROM_SINK_RFB ; 
 int /*<<< orphan*/  dc_link_set_psr_enable (struct dc_link const*,int,int) ; 
 int /*<<< orphan*/  dm_helpers_dp_read_dpcd (int /*<<< orphan*/ ,struct dc_link const*,int,unsigned char*,int) ; 
 int /*<<< orphan*/  dm_helpers_dp_write_dpcd (int /*<<< orphan*/ ,struct dc_link const*,int,unsigned char*,int) ; 

__attribute__((used)) static bool handle_hpd_irq_psr_sink(const struct dc_link *link)
{
	union dpcd_psr_configuration psr_configuration;

	if (!link->psr_enabled)
		return false;

	dm_helpers_dp_read_dpcd(
		link->ctx,
		link,
		368,/*DpcdAddress_PSR_Enable_Cfg*/
		&psr_configuration.raw,
		sizeof(psr_configuration.raw));


	if (psr_configuration.bits.ENABLE) {
		unsigned char dpcdbuf[3] = {0};
		union psr_error_status psr_error_status;
		union psr_sink_psr_status psr_sink_psr_status;

		dm_helpers_dp_read_dpcd(
			link->ctx,
			link,
			0x2006, /*DpcdAddress_PSR_Error_Status*/
			(unsigned char *) dpcdbuf,
			sizeof(dpcdbuf));

		/*DPCD 2006h   ERROR STATUS*/
		psr_error_status.raw = dpcdbuf[0];
		/*DPCD 2008h   SINK PANEL SELF REFRESH STATUS*/
		psr_sink_psr_status.raw = dpcdbuf[2];

		if (psr_error_status.bits.LINK_CRC_ERROR ||
				psr_error_status.bits.RFB_STORAGE_ERROR) {
			/* Acknowledge and clear error bits */
			dm_helpers_dp_write_dpcd(
				link->ctx,
				link,
				8198,/*DpcdAddress_PSR_Error_Status*/
				&psr_error_status.raw,
				sizeof(psr_error_status.raw));

			/* PSR error, disable and re-enable PSR */
			dc_link_set_psr_enable(link, false, true);
			dc_link_set_psr_enable(link, true, true);

			return true;
		} else if (psr_sink_psr_status.bits.SINK_SELF_REFRESH_STATUS ==
				PSR_SINK_STATE_ACTIVE_DISPLAY_FROM_SINK_RFB){
			/* No error is detect, PSR is active.
			 * We should return with IRQ_HPD handled without
			 * checking for loss of sync since PSR would have
			 * powered down main link.
			 */
			return true;
		}
	}
	return false;
}