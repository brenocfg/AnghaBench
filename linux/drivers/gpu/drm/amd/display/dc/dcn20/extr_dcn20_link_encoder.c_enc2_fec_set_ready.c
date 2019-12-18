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
 int /*<<< orphan*/  DPHY_FEC_READY_SHADOW ; 
 int /*<<< orphan*/  DP_DPHY_CNTL ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct dcn10_link_encoder* TO_DCN10_LINK_ENC (struct link_encoder*) ; 

void enc2_fec_set_ready(struct link_encoder *enc, bool ready)
{
	struct dcn10_link_encoder *enc10 = TO_DCN10_LINK_ENC(enc);

	REG_UPDATE(DP_DPHY_CNTL, DPHY_FEC_READY_SHADOW, ready);
}