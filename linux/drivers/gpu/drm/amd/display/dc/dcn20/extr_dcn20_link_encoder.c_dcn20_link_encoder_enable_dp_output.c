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
struct link_encoder {TYPE_3__* ctx; } ;
struct dpcssys_phy_seq_cfg {int dummy; } ;
struct dcn20_link_encoder {struct dpcssys_phy_seq_cfg phy_seq_cfg; } ;
struct dcn10_link_encoder {int dummy; } ;
struct dc_link_settings {int dummy; } ;
typedef  enum clock_source_id { ____Placeholder_clock_source_id } clock_source_id ;
struct TYPE_6__ {TYPE_2__* dc; } ;
struct TYPE_4__ {int /*<<< orphan*/  avoid_vbios_exec_table; } ;
struct TYPE_5__ {TYPE_1__ debug; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGNAL_TYPE_DISPLAY_PORT ; 
 struct dcn10_link_encoder* TO_DCN10_LINK_ENC (struct link_encoder*) ; 
 int /*<<< orphan*/  dcn10_link_encoder_enable_dp_output (struct link_encoder*,struct dc_link_settings const*,int) ; 
 int /*<<< orphan*/  dcn10_link_encoder_setup (struct link_encoder*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enc1_configure_encoder (struct dcn10_link_encoder*,struct dc_link_settings const*) ; 
 int /*<<< orphan*/  update_cfg_data (struct dcn10_link_encoder*,struct dc_link_settings const*,struct dpcssys_phy_seq_cfg*) ; 

void dcn20_link_encoder_enable_dp_output(
	struct link_encoder *enc,
	const struct dc_link_settings *link_settings,
	enum clock_source_id clock_source)
{
	struct dcn10_link_encoder *enc10 = TO_DCN10_LINK_ENC(enc);
	struct dcn20_link_encoder *enc20 = (struct dcn20_link_encoder *) enc10;
	struct dpcssys_phy_seq_cfg *cfg = &enc20->phy_seq_cfg;

	if (!enc->ctx->dc->debug.avoid_vbios_exec_table) {
		dcn10_link_encoder_enable_dp_output(enc, link_settings, clock_source);
		return;
	}

	if (!update_cfg_data(enc10, link_settings, cfg))
		return;

	enc1_configure_encoder(enc10, link_settings);

	dcn10_link_encoder_setup(enc, SIGNAL_TYPE_DISPLAY_PORT);

}