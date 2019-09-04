#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ IS_TPS4_CAPABLE; scalar_t__ IS_TPS3_CAPABLE; } ;
struct TYPE_14__ {TYPE_6__ bits; } ;
struct encoder_feature_support {TYPE_7__ flags; } ;
struct TYPE_10__ {scalar_t__ TPS3_SUPPORTED; } ;
struct TYPE_11__ {TYPE_3__ bits; } ;
struct TYPE_8__ {scalar_t__ TPS4_SUPPORTED; } ;
struct TYPE_9__ {TYPE_1__ bits; } ;
struct dpcd_caps {TYPE_4__ max_ln_count; TYPE_2__ max_down_spread; } ;
struct dc_link {struct dpcd_caps dpcd_caps; TYPE_5__* link_enc; } ;
typedef  enum hw_dp_training_pattern { ____Placeholder_hw_dp_training_pattern } hw_dp_training_pattern ;
struct TYPE_12__ {struct encoder_feature_support features; } ;

/* Variables and functions */
 int HW_DP_TRAINING_PATTERN_2 ; 
 int HW_DP_TRAINING_PATTERN_3 ; 
 int HW_DP_TRAINING_PATTERN_4 ; 

__attribute__((used)) static enum hw_dp_training_pattern get_supported_tp(struct dc_link *link)
{
	enum hw_dp_training_pattern highest_tp = HW_DP_TRAINING_PATTERN_2;
	struct encoder_feature_support *features = &link->link_enc->features;
	struct dpcd_caps *dpcd_caps = &link->dpcd_caps;

	if (features->flags.bits.IS_TPS3_CAPABLE)
		highest_tp = HW_DP_TRAINING_PATTERN_3;

	if (features->flags.bits.IS_TPS4_CAPABLE)
		highest_tp = HW_DP_TRAINING_PATTERN_4;

	if (dpcd_caps->max_down_spread.bits.TPS4_SUPPORTED &&
		highest_tp >= HW_DP_TRAINING_PATTERN_4)
		return HW_DP_TRAINING_PATTERN_4;

	if (dpcd_caps->max_ln_count.bits.TPS3_SUPPORTED &&
		highest_tp >= HW_DP_TRAINING_PATTERN_3)
		return HW_DP_TRAINING_PATTERN_3;

	return HW_DP_TRAINING_PATTERN_2;
}