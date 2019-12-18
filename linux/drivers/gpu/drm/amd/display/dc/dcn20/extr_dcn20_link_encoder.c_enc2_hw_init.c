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
struct link_encoder {int dummy; } ;
struct dcn10_link_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUX_DPHY_RX_CONTROL0 ; 
 int /*<<< orphan*/  AUX_DPHY_TX_CONTROL ; 
 int /*<<< orphan*/  AUX_REG_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TMDS_CTL0 ; 
 int /*<<< orphan*/  TMDS_CTL_BITS ; 
 struct dcn10_link_encoder* TO_DCN10_LINK_ENC (struct link_encoder*) ; 
 int /*<<< orphan*/  dcn10_aux_initialize (struct dcn10_link_encoder*) ; 

void enc2_hw_init(struct link_encoder *enc)
{
	struct dcn10_link_encoder *enc10 = TO_DCN10_LINK_ENC(enc);

/*
	00 - DP_AUX_DPHY_RX_DETECTION_THRESHOLD__1to2 : 1/2
	01 - DP_AUX_DPHY_RX_DETECTION_THRESHOLD__3to4 : 3/4
	02 - DP_AUX_DPHY_RX_DETECTION_THRESHOLD__7to8 : 7/8
	03 - DP_AUX_DPHY_RX_DETECTION_THRESHOLD__15to16 : 15/16
	04 - DP_AUX_DPHY_RX_DETECTION_THRESHOLD__31to32 : 31/32
	05 - DP_AUX_DPHY_RX_DETECTION_THRESHOLD__63to64 : 63/64
	06 - DP_AUX_DPHY_RX_DETECTION_THRESHOLD__127to128 : 127/128
	07 - DP_AUX_DPHY_RX_DETECTION_THRESHOLD__255to256 : 255/256
*/

/*
	AUX_REG_UPDATE_5(AUX_DPHY_RX_CONTROL0,
	AUX_RX_START_WINDOW = 1 [6:4]
	AUX_RX_RECEIVE_WINDOW = 1 default is 2 [10:8]
	AUX_RX_HALF_SYM_DETECT_LEN  = 1 [13:12] default is 1
	AUX_RX_TRANSITION_FILTER_EN = 1 [16] default is 1
	AUX_RX_ALLOW_BELOW_THRESHOLD_PHASE_DETECT [17] is 0  default is 0
	AUX_RX_ALLOW_BELOW_THRESHOLD_START [18] is 1  default is 1
	AUX_RX_ALLOW_BELOW_THRESHOLD_STOP [19] is 1  default is 1
	AUX_RX_PHASE_DETECT_LEN,  [21,20] = 0x3 default is 3
	AUX_RX_DETECTION_THRESHOLD [30:28] = 1
*/
	AUX_REG_WRITE(AUX_DPHY_RX_CONTROL0, 0x103d1110);

	AUX_REG_WRITE(AUX_DPHY_TX_CONTROL, 0x21c7a);

	//AUX_DPHY_TX_REF_CONTROL'AUX_TX_REF_DIV HW default is 0x32;
	// Set AUX_TX_REF_DIV Divider to generate 2 MHz reference from refclk
	// 27MHz -> 0xd
	// 100MHz -> 0x32
	// 48MHz -> 0x18

	// Set TMDS_CTL0 to 1.  This is a legacy setting.
	REG_UPDATE(TMDS_CTL_BITS, TMDS_CTL0, 1);

	dcn10_aux_initialize(enc10);
}