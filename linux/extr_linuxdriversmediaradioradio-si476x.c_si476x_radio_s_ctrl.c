#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct v4l2_ctrl {int id; int val; int /*<<< orphan*/  handler; } ;
struct si476x_radio {TYPE_3__* core; TYPE_2__* ops; } ;
typedef  enum si476x_phase_diversity_mode { ____Placeholder_si476x_phase_diversity_mode } si476x_phase_diversity_mode ;
struct TYPE_10__ {int rds_fifo_depth; int diversity_mode; int /*<<< orphan*/  regmap; TYPE_1__* client; } ;
struct TYPE_9__ {int (* phase_diversity ) (TYPE_3__*,int) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SI476X_PROP_AUDIO_DEEMPHASIS ; 
 int /*<<< orphan*/  SI476X_PROP_AUDIO_PWR_LINE_FILTER ; 
 int /*<<< orphan*/  SI476X_PROP_FM_RDS_CONFIG ; 
 int /*<<< orphan*/  SI476X_PROP_FM_RDS_INTERRUPT_FIFO_COUNT ; 
 int /*<<< orphan*/  SI476X_PROP_FM_RDS_INTERRUPT_SOURCE ; 
 int /*<<< orphan*/  SI476X_PROP_PWR_ENABLE_MASK ; 
 int SI476X_PROP_PWR_GRID_50HZ ; 
 int SI476X_PROP_PWR_GRID_60HZ ; 
 int /*<<< orphan*/  SI476X_PROP_PWR_GRID_MASK ; 
 int /*<<< orphan*/  SI476X_PROP_PWR_HARMONICS_MASK ; 
 int SI476X_PROP_RDSEN ; 
 int /*<<< orphan*/  SI476X_PROP_RDSEN_MASK ; 
 int /*<<< orphan*/  SI476X_PROP_VALID_MAX_TUNE_ERROR ; 
 int /*<<< orphan*/  SI476X_PROP_VALID_RSSI_THRESHOLD ; 
 int /*<<< orphan*/  SI476X_PROP_VALID_SNR_THRESHOLD ; 
 int SI476X_RDSRECV ; 
#define  V4L2_CID_POWER_LINE_FREQUENCY 138 
#define  V4L2_CID_POWER_LINE_FREQUENCY_50HZ 137 
#define  V4L2_CID_POWER_LINE_FREQUENCY_60HZ 136 
#define  V4L2_CID_POWER_LINE_FREQUENCY_DISABLED 135 
#define  V4L2_CID_RDS_RECEPTION 134 
#define  V4L2_CID_SI476X_DIVERSITY_MODE 133 
#define  V4L2_CID_SI476X_HARMONICS_COUNT 132 
#define  V4L2_CID_SI476X_MAX_TUNE_ERROR 131 
#define  V4L2_CID_SI476X_RSSI_THRESHOLD 130 
#define  V4L2_CID_SI476X_SNR_THRESHOLD 129 
#define  V4L2_CID_TUNE_DEEMPHASIS 128 
 int /*<<< orphan*/  regcache_cache_only (int /*<<< orphan*/ ,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int si476x_core_cmd_fm_rds_status (TYPE_3__*,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  si476x_core_is_in_am_receiver_mode (TYPE_3__*) ; 
 int /*<<< orphan*/  si476x_core_lock (TYPE_3__*) ; 
 int /*<<< orphan*/  si476x_core_unlock (TYPE_3__*) ; 
 int si476x_phase_diversity_idx_to_mode (int) ; 
 int stub1 (TYPE_3__*,int) ; 
 struct si476x_radio* v4l2_ctrl_handler_to_radio (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int si476x_radio_s_ctrl(struct v4l2_ctrl *ctrl)
{
	int retval;
	enum si476x_phase_diversity_mode mode;
	struct si476x_radio *radio = v4l2_ctrl_handler_to_radio(ctrl->handler);

	si476x_core_lock(radio->core);

	switch (ctrl->id) {
	case V4L2_CID_SI476X_HARMONICS_COUNT:
		retval = regmap_update_bits(radio->core->regmap,
					    SI476X_PROP_AUDIO_PWR_LINE_FILTER,
					    SI476X_PROP_PWR_HARMONICS_MASK,
					    ctrl->val);
		break;
	case V4L2_CID_POWER_LINE_FREQUENCY:
		switch (ctrl->val) {
		case V4L2_CID_POWER_LINE_FREQUENCY_DISABLED:
			retval = regmap_update_bits(radio->core->regmap,
						    SI476X_PROP_AUDIO_PWR_LINE_FILTER,
						    SI476X_PROP_PWR_ENABLE_MASK,
						    0);
			break;
		case V4L2_CID_POWER_LINE_FREQUENCY_50HZ:
			retval = regmap_update_bits(radio->core->regmap,
						    SI476X_PROP_AUDIO_PWR_LINE_FILTER,
						    SI476X_PROP_PWR_GRID_MASK,
						    SI476X_PROP_PWR_GRID_50HZ);
			break;
		case V4L2_CID_POWER_LINE_FREQUENCY_60HZ:
			retval = regmap_update_bits(radio->core->regmap,
						    SI476X_PROP_AUDIO_PWR_LINE_FILTER,
						    SI476X_PROP_PWR_GRID_MASK,
						    SI476X_PROP_PWR_GRID_60HZ);
			break;
		default:
			retval = -EINVAL;
			break;
		}
		break;
	case V4L2_CID_SI476X_RSSI_THRESHOLD:
		retval = regmap_write(radio->core->regmap,
				      SI476X_PROP_VALID_RSSI_THRESHOLD,
				      ctrl->val);
		break;
	case V4L2_CID_SI476X_SNR_THRESHOLD:
		retval = regmap_write(radio->core->regmap,
				      SI476X_PROP_VALID_SNR_THRESHOLD,
				      ctrl->val);
		break;
	case V4L2_CID_SI476X_MAX_TUNE_ERROR:
		retval = regmap_write(radio->core->regmap,
				      SI476X_PROP_VALID_MAX_TUNE_ERROR,
				      ctrl->val);
		break;
	case V4L2_CID_RDS_RECEPTION:
		/*
		 * It looks like RDS related properties are
		 * inaccesable when tuner is in AM mode, so cache the
		 * changes
		 */
		if (si476x_core_is_in_am_receiver_mode(radio->core))
			regcache_cache_only(radio->core->regmap, true);

		if (ctrl->val) {
			retval = regmap_write(radio->core->regmap,
					      SI476X_PROP_FM_RDS_INTERRUPT_FIFO_COUNT,
					      radio->core->rds_fifo_depth);
			if (retval < 0)
				break;

			if (radio->core->client->irq) {
				retval = regmap_write(radio->core->regmap,
						      SI476X_PROP_FM_RDS_INTERRUPT_SOURCE,
						      SI476X_RDSRECV);
				if (retval < 0)
					break;
			}

			/* Drain RDS FIFO before enabling RDS processing */
			retval = si476x_core_cmd_fm_rds_status(radio->core,
							       false,
							       true,
							       true,
							       NULL);
			if (retval < 0)
				break;

			retval = regmap_update_bits(radio->core->regmap,
						    SI476X_PROP_FM_RDS_CONFIG,
						    SI476X_PROP_RDSEN_MASK,
						    SI476X_PROP_RDSEN);
		} else {
			retval = regmap_update_bits(radio->core->regmap,
						    SI476X_PROP_FM_RDS_CONFIG,
						    SI476X_PROP_RDSEN_MASK,
						    !SI476X_PROP_RDSEN);
		}

		if (si476x_core_is_in_am_receiver_mode(radio->core))
			regcache_cache_only(radio->core->regmap, false);
		break;
	case V4L2_CID_TUNE_DEEMPHASIS:
		retval = regmap_write(radio->core->regmap,
				      SI476X_PROP_AUDIO_DEEMPHASIS,
				      ctrl->val);
		break;

	case V4L2_CID_SI476X_DIVERSITY_MODE:
		mode = si476x_phase_diversity_idx_to_mode(ctrl->val);

		if (mode == radio->core->diversity_mode) {
			retval = 0;
			break;
		}

		if (si476x_core_is_in_am_receiver_mode(radio->core)) {
			/*
			 * Diversity cannot be configured while tuner
			 * is in AM mode so save the changes and carry on.
			 */
			radio->core->diversity_mode = mode;
			retval = 0;
		} else {
			retval = radio->ops->phase_diversity(radio->core, mode);
			if (!retval)
				radio->core->diversity_mode = mode;
		}
		break;

	default:
		retval = -EINVAL;
		break;
	}

	si476x_core_unlock(radio->core);

	return retval;
}