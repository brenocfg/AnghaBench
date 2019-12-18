#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct radeon_encoder_atom_dig {scalar_t__ linkb; scalar_t__ dig_encoder; } ;
struct radeon_encoder {struct radeon_encoder_atom_dig* enc_priv; } ;
struct radeon_dp_link_train_info {int use_dpencoder; int tp3_supported; int /*<<< orphan*/ * aux; int /*<<< orphan*/  dp_clock; int /*<<< orphan*/  dp_lane_count; struct drm_connector* connector; struct drm_encoder* encoder; struct radeon_device* rdev; int /*<<< orphan*/  dpcd; int /*<<< orphan*/  enc_id; } ;
struct TYPE_3__ {int /*<<< orphan*/  atom_context; } ;
struct radeon_device {TYPE_1__ mode_info; } ;
struct radeon_connector_atom_dig {scalar_t__ dp_sink_type; int /*<<< orphan*/  dp_clock; int /*<<< orphan*/  dp_lane_count; int /*<<< orphan*/  dpcd; } ;
struct radeon_connector {TYPE_2__* ddc_bus; struct radeon_connector_atom_dig* con_priv; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct drm_connector {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  aux; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_DCE5 (struct radeon_device*) ; 
 int /*<<< orphan*/  ATOM_DP_CONFIG_DIG1_ENCODER ; 
 int /*<<< orphan*/  ATOM_DP_CONFIG_DIG2_ENCODER ; 
 int /*<<< orphan*/  ATOM_DP_CONFIG_LINK_A ; 
 int /*<<< orphan*/  ATOM_DP_CONFIG_LINK_B ; 
 int /*<<< orphan*/  COMMAND ; 
 scalar_t__ CONNECTOR_OBJECT_ID_DISPLAYPORT ; 
 scalar_t__ CONNECTOR_OBJECT_ID_eDP ; 
 int /*<<< orphan*/  DPEncoderService ; 
 int /*<<< orphan*/  DP_MAX_LANE_COUNT ; 
 int /*<<< orphan*/  DP_RECEIVER_CAP_SIZE ; 
 int DP_TPS3_SUPPORTED ; 
 int GetIndexIntoMasterTable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ atom_parse_cmd_header (int /*<<< orphan*/ ,int,int*,int*) ; 
 int drm_dp_dpcd_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ radeon_dp_link_train_ce (struct radeon_dp_link_train_info*) ; 
 scalar_t__ radeon_dp_link_train_cr (struct radeon_dp_link_train_info*) ; 
 scalar_t__ radeon_dp_link_train_finish (struct radeon_dp_link_train_info*) ; 
 scalar_t__ radeon_dp_link_train_init (struct radeon_dp_link_train_info*) ; 
 struct radeon_connector* to_radeon_connector (struct drm_connector*) ; 
 struct radeon_encoder* to_radeon_encoder (struct drm_encoder*) ; 

void radeon_dp_link_train(struct drm_encoder *encoder,
			  struct drm_connector *connector)
{
	struct drm_device *dev = encoder->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	struct radeon_encoder_atom_dig *dig;
	struct radeon_connector *radeon_connector;
	struct radeon_connector_atom_dig *dig_connector;
	struct radeon_dp_link_train_info dp_info;
	int index;
	u8 tmp, frev, crev;

	if (!radeon_encoder->enc_priv)
		return;
	dig = radeon_encoder->enc_priv;

	radeon_connector = to_radeon_connector(connector);
	if (!radeon_connector->con_priv)
		return;
	dig_connector = radeon_connector->con_priv;

	if ((dig_connector->dp_sink_type != CONNECTOR_OBJECT_ID_DISPLAYPORT) &&
	    (dig_connector->dp_sink_type != CONNECTOR_OBJECT_ID_eDP))
		return;

	/* DPEncoderService newer than 1.1 can't program properly the
	 * training pattern. When facing such version use the
	 * DIGXEncoderControl (X== 1 | 2)
	 */
	dp_info.use_dpencoder = true;
	index = GetIndexIntoMasterTable(COMMAND, DPEncoderService);
	if (atom_parse_cmd_header(rdev->mode_info.atom_context, index, &frev, &crev)) {
		if (crev > 1) {
			dp_info.use_dpencoder = false;
		}
	}

	dp_info.enc_id = 0;
	if (dig->dig_encoder)
		dp_info.enc_id |= ATOM_DP_CONFIG_DIG2_ENCODER;
	else
		dp_info.enc_id |= ATOM_DP_CONFIG_DIG1_ENCODER;
	if (dig->linkb)
		dp_info.enc_id |= ATOM_DP_CONFIG_LINK_B;
	else
		dp_info.enc_id |= ATOM_DP_CONFIG_LINK_A;

	if (drm_dp_dpcd_readb(&radeon_connector->ddc_bus->aux, DP_MAX_LANE_COUNT, &tmp)
	    == 1) {
		if (ASIC_IS_DCE5(rdev) && (tmp & DP_TPS3_SUPPORTED))
			dp_info.tp3_supported = true;
		else
			dp_info.tp3_supported = false;
	} else {
		dp_info.tp3_supported = false;
	}

	memcpy(dp_info.dpcd, dig_connector->dpcd, DP_RECEIVER_CAP_SIZE);
	dp_info.rdev = rdev;
	dp_info.encoder = encoder;
	dp_info.connector = connector;
	dp_info.dp_lane_count = dig_connector->dp_lane_count;
	dp_info.dp_clock = dig_connector->dp_clock;
	dp_info.aux = &radeon_connector->ddc_bus->aux;

	if (radeon_dp_link_train_init(&dp_info))
		goto done;
	if (radeon_dp_link_train_cr(&dp_info))
		goto done;
	if (radeon_dp_link_train_ce(&dp_info))
		goto done;
done:
	if (radeon_dp_link_train_finish(&dp_info))
		return;
}