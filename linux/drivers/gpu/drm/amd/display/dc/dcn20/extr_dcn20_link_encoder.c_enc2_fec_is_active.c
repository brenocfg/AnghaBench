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
typedef  scalar_t__ uint32_t ;
struct link_encoder {int dummy; } ;
struct dcn10_link_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPHY_FEC_ACTIVE_STATUS ; 
 int /*<<< orphan*/  DP_DPHY_CNTL ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 struct dcn10_link_encoder* TO_DCN10_LINK_ENC (struct link_encoder*) ; 

bool enc2_fec_is_active(struct link_encoder *enc)
{
	uint32_t active = 0;
	struct dcn10_link_encoder *enc10 = TO_DCN10_LINK_ENC(enc);

	REG_GET(DP_DPHY_CNTL, DPHY_FEC_ACTIVE_STATUS, &active);

	return (active != 0);
}