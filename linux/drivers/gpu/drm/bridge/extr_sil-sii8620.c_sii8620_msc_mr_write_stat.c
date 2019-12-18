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
typedef  int u8 ;
struct sii8620 {int* stat; int* xstat; } ;

/* Variables and functions */
 size_t MHL_DST_CONNECTED_RDY ; 
 int MHL_DST_CONN_DCAP_RDY ; 
 size_t MHL_DST_LINK_MODE ; 
 int MHL_DST_LM_PATH_ENABLED ; 
 int MHL_DST_SIZE ; 
 int MHL_XDS_SIZE ; 
 int /*<<< orphan*/  REG_MHL_EXTSTAT_0 ; 
 int /*<<< orphan*/  REG_MHL_STAT_0 ; 
 int /*<<< orphan*/  sii8620_is_mhl3 (struct sii8620*) ; 
 int /*<<< orphan*/  sii8620_mt_read_devcap (struct sii8620*,int) ; 
 int /*<<< orphan*/  sii8620_read_buf (struct sii8620*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  sii8620_status_changed_path (struct sii8620*) ; 
 int /*<<< orphan*/  sii8620_status_dcap_ready (struct sii8620*) ; 
 int /*<<< orphan*/  sii8620_update_array (int*,int*,int) ; 

__attribute__((used)) static void sii8620_msc_mr_write_stat(struct sii8620 *ctx)
{
	u8 st[MHL_DST_SIZE], xst[MHL_XDS_SIZE];

	sii8620_read_buf(ctx, REG_MHL_STAT_0, st, MHL_DST_SIZE);
	sii8620_read_buf(ctx, REG_MHL_EXTSTAT_0, xst, MHL_XDS_SIZE);

	sii8620_update_array(ctx->stat, st, MHL_DST_SIZE);
	sii8620_update_array(ctx->xstat, xst, MHL_XDS_SIZE);

	if (ctx->stat[MHL_DST_CONNECTED_RDY] & st[MHL_DST_CONNECTED_RDY] &
	    MHL_DST_CONN_DCAP_RDY) {
		sii8620_status_dcap_ready(ctx);

		if (!sii8620_is_mhl3(ctx))
			sii8620_mt_read_devcap(ctx, false);
	}

	if (st[MHL_DST_LINK_MODE] & MHL_DST_LM_PATH_ENABLED)
		sii8620_status_changed_path(ctx);
}