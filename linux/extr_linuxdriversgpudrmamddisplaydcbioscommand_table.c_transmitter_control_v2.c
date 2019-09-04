#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  void* uint16_t ;
struct TYPE_12__ {scalar_t__ id; } ;
struct bp_transmitter_control {int transmitter; int action; int pixel_clock; scalar_t__ engine_id; int /*<<< orphan*/  coherent; int /*<<< orphan*/  lanes_number; scalar_t__ lane_settings; scalar_t__ lane_select; TYPE_6__ connector_obj_id; } ;
struct bios_parser {TYPE_3__* cmd_helper; } ;
typedef  int /*<<< orphan*/  params ;
typedef  enum connector_id { ____Placeholder_connector_id } connector_id ;
typedef  enum bp_result { ____Placeholder_bp_result } bp_result ;
struct TYPE_9__ {int fDualLinkConnector; int ucLinkSel; int ucEncoderSel; int fDPConnector; void* ucTransmitterSel; int /*<<< orphan*/  fCoherentMode; } ;
struct TYPE_8__ {void* ucLaneSet; void* ucLaneSel; } ;
struct TYPE_11__ {void* ucAction; TYPE_2__ acConfig; void* usPixelClock; TYPE_1__ asMode; void* usInitInfo; } ;
struct TYPE_10__ {scalar_t__ (* transmitter_bp_to_atom ) (int const) ;} ;
typedef  TYPE_4__ DIG_TRANSMITTER_CONTROL_PARAMETERS_V2 ;

/* Variables and functions */
 int BP_RESULT_BADINPUT ; 
 int BP_RESULT_FAILURE ; 
 int BP_RESULT_OK ; 
 int CONNECTOR_ID_DISPLAY_PORT ; 
 int CONNECTOR_ID_DUAL_LINK_DVID ; 
 int CONNECTOR_ID_DUAL_LINK_DVII ; 
 scalar_t__ ENGINE_ID_DIGB ; 
 scalar_t__ EXEC_BIOS_CMD_TABLE (int /*<<< orphan*/ ,TYPE_4__) ; 
 int /*<<< orphan*/  LANE_COUNT_FOUR ; 
#define  TRANSMITTER_CONTROL_INIT 136 
#define  TRANSMITTER_CONTROL_SET_VOLTAGE_AND_PREEMPASIS 135 
#define  TRANSMITTER_TRAVIS_LCD 134 
#define  TRANSMITTER_UNIPHY_A 133 
#define  TRANSMITTER_UNIPHY_B 132 
#define  TRANSMITTER_UNIPHY_C 131 
#define  TRANSMITTER_UNIPHY_D 130 
#define  TRANSMITTER_UNIPHY_E 129 
#define  TRANSMITTER_UNIPHY_F 128 
 int /*<<< orphan*/  UNIPHYTransmitterControl ; 
 void* cpu_to_le16 (void*) ; 
 int dal_graphics_object_id_get_connector_id (TYPE_6__) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (int const) ; 

__attribute__((used)) static enum bp_result transmitter_control_v2(
	struct bios_parser *bp,
	struct bp_transmitter_control *cntl)
{
	enum bp_result result = BP_RESULT_FAILURE;
	DIG_TRANSMITTER_CONTROL_PARAMETERS_V2 params;
	enum connector_id connector_id =
		dal_graphics_object_id_get_connector_id(cntl->connector_obj_id);

	memset(&params, 0, sizeof(params));

	switch (cntl->transmitter) {
	case TRANSMITTER_UNIPHY_A:
	case TRANSMITTER_UNIPHY_B:
	case TRANSMITTER_UNIPHY_C:
	case TRANSMITTER_UNIPHY_D:
	case TRANSMITTER_UNIPHY_E:
	case TRANSMITTER_UNIPHY_F:
	case TRANSMITTER_TRAVIS_LCD:
		break;
	default:
		return BP_RESULT_BADINPUT;
	}

	switch (cntl->action) {
	case TRANSMITTER_CONTROL_INIT:
		if ((CONNECTOR_ID_DUAL_LINK_DVII == connector_id) ||
				(CONNECTOR_ID_DUAL_LINK_DVID == connector_id))
			/* on INIT this bit should be set according to the
			 * phisycal connector
			 * Bit0: dual link connector flag
			 * =0 connector is single link connector
			 * =1 connector is dual link connector
			 */
			params.acConfig.fDualLinkConnector = 1;

		/* connector object id */
		params.usInitInfo =
				cpu_to_le16((uint8_t)cntl->connector_obj_id.id);
		break;
	case TRANSMITTER_CONTROL_SET_VOLTAGE_AND_PREEMPASIS:
		/* votage swing and pre-emphsis */
		params.asMode.ucLaneSel = (uint8_t)cntl->lane_select;
		params.asMode.ucLaneSet = (uint8_t)cntl->lane_settings;
		break;
	default:
		/* if dual-link */
		if (LANE_COUNT_FOUR < cntl->lanes_number) {
			/* on ENABLE/DISABLE this bit should be set according to
			 * actual timing (number of lanes)
			 * Bit0: dual link connector flag
			 * =0 connector is single link connector
			 * =1 connector is dual link connector
			 */
			params.acConfig.fDualLinkConnector = 1;

			/* link rate, half for dual link
			 * We need to convert from KHz units into 20KHz units
			 */
			params.usPixelClock =
					cpu_to_le16((uint16_t)(cntl->pixel_clock / 20));
		} else
			/* link rate, half for dual link
			 * We need to convert from KHz units into 10KHz units
			 */
			params.usPixelClock =
					cpu_to_le16((uint16_t)(cntl->pixel_clock / 10));
		break;
	}

	/* 00 - coherent mode
	 * 01 - incoherent mode
	 */

	params.acConfig.fCoherentMode = cntl->coherent;

	if ((TRANSMITTER_UNIPHY_B == cntl->transmitter)
			|| (TRANSMITTER_UNIPHY_D == cntl->transmitter)
			|| (TRANSMITTER_UNIPHY_F == cntl->transmitter))
		/* Bit2: Transmitter Link selection
		 * =0 when bit0=0, single link A/C/E, when bit0=1,
		 * master link A/C/E
		 * =1 when bit0=0, single link B/D/F, when bit0=1,
		 * master link B/D/F
		 */
		params.acConfig.ucLinkSel = 1;

	if (ENGINE_ID_DIGB == cntl->engine_id)
		/* Bit3: Transmitter data source selection
		 * =0 DIGA is data source.
		 * =1 DIGB is data source.
		 * This bit is only useful when ucAction= ATOM_ENABLE
		 */
		params.acConfig.ucEncoderSel = 1;

	if (CONNECTOR_ID_DISPLAY_PORT == connector_id)
		/* Bit4: DP connector flag
		 * =0 connector is none-DP connector
		 * =1 connector is DP connector
		 */
		params.acConfig.fDPConnector = 1;

	/* Bit[7:6]: Transmitter selection
	 * =0 UNIPHY_ENCODER: UNIPHYA/B
	 * =1 UNIPHY1_ENCODER: UNIPHYC/D
	 * =2 UNIPHY2_ENCODER: UNIPHYE/F
	 * =3 reserved
	 */
	params.acConfig.ucTransmitterSel =
			(uint8_t)bp->cmd_helper->transmitter_bp_to_atom(
					cntl->transmitter);

	params.ucAction = (uint8_t)cntl->action;

	if (EXEC_BIOS_CMD_TABLE(UNIPHYTransmitterControl, params))
		result = BP_RESULT_OK;

	return result;
}