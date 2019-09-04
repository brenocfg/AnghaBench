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
struct dce110_link_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_SEC_CNTL1 ; 
 int /*<<< orphan*/  DP_SEC_GSP0_LINE_NUM ; 
 int /*<<< orphan*/  DP_SEC_GSP0_PRIORITY ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int) ; 
 struct dce110_link_encoder* TO_DCE110_LINK_ENC (struct link_encoder*) ; 

void dce110_psr_program_secondary_packet(struct link_encoder *enc,
			unsigned int sdp_transmit_line_num_deadline)
{
	struct dce110_link_encoder *enc110 = TO_DCE110_LINK_ENC(enc);

	REG_UPDATE_2(DP_SEC_CNTL1,
		DP_SEC_GSP0_LINE_NUM, sdp_transmit_line_num_deadline,
		DP_SEC_GSP0_PRIORITY, 1);
}