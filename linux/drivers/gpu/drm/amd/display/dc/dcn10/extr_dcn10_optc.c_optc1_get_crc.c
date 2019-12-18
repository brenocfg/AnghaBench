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
struct timing_generator {int dummy; } ;
struct optc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRC0_B_CB ; 
 int /*<<< orphan*/  CRC0_G_Y ; 
 int /*<<< orphan*/  CRC0_R_CR ; 
 struct optc* DCN10TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  OTG_CRC0_DATA_B ; 
 int /*<<< orphan*/  OTG_CRC0_DATA_RG ; 
 int /*<<< orphan*/  OTG_CRC_CNTL ; 
 int /*<<< orphan*/  OTG_CRC_EN ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  REG_GET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,scalar_t__*) ; 

bool optc1_get_crc(struct timing_generator *optc,
		    uint32_t *r_cr, uint32_t *g_y, uint32_t *b_cb)
{
	uint32_t field = 0;
	struct optc *optc1 = DCN10TG_FROM_TG(optc);

	REG_GET(OTG_CRC_CNTL, OTG_CRC_EN, &field);

	/* Early return if CRC is not enabled for this CRTC */
	if (!field)
		return false;

	REG_GET_2(OTG_CRC0_DATA_RG,
			CRC0_R_CR, r_cr,
			CRC0_G_Y, g_y);

	REG_GET(OTG_CRC0_DATA_B,
			CRC0_B_CB, b_cb);

	return true;
}