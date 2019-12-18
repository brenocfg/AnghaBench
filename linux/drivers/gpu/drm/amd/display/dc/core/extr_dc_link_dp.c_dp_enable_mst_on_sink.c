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
struct dc_link {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_MSTM_CTRL ; 
 unsigned char DP_MST_EN ; 
 int /*<<< orphan*/  core_link_read_dpcd (struct dc_link*,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  core_link_write_dpcd (struct dc_link*,int /*<<< orphan*/ ,unsigned char*,int) ; 

void dp_enable_mst_on_sink(struct dc_link *link, bool enable)
{
	unsigned char mstmCntl;

	core_link_read_dpcd(link, DP_MSTM_CTRL, &mstmCntl, 1);
	if (enable)
		mstmCntl |= DP_MST_EN;
	else
		mstmCntl &= (~DP_MST_EN);

	core_link_write_dpcd(link, DP_MSTM_CTRL, &mstmCntl, 1);
}