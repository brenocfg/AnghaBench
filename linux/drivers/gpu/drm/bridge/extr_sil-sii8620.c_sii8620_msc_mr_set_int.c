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
struct sii8620 {int mode; int feature_complete; scalar_t__ edid; } ;

/* Variables and functions */
#define  CM_ECBUS_S 129 
#define  CM_MHL3 128 
 size_t MHL_INT_RCHANGE ; 
 int MHL_INT_RC_DCAP_CHG ; 
 int MHL_INT_RC_FEAT_COMPLETE ; 
 int MHL_INT_RC_FEAT_REQ ; 
 int MHL_INT_SIZE ; 
 int /*<<< orphan*/  MHL_XDC_ECBUS_SPEEDS ; 
 int /*<<< orphan*/  REG_MHL_INT_0 ; 
 int /*<<< orphan*/  sii8620_enable_hpd (struct sii8620*) ; 
 int /*<<< orphan*/  sii8620_got_ecbus_speed ; 
 int /*<<< orphan*/  sii8620_mt_read_devcap (struct sii8620*,int) ; 
 int /*<<< orphan*/  sii8620_mt_read_xdevcap_reg (struct sii8620*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sii8620_mt_set_cont (struct sii8620*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sii8620_read_buf (struct sii8620*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  sii8620_send_features (struct sii8620*) ; 
 int /*<<< orphan*/  sii8620_write_buf (struct sii8620*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void sii8620_msc_mr_set_int(struct sii8620 *ctx)
{
	u8 ints[MHL_INT_SIZE];

	sii8620_read_buf(ctx, REG_MHL_INT_0, ints, MHL_INT_SIZE);
	sii8620_write_buf(ctx, REG_MHL_INT_0, ints, MHL_INT_SIZE);

	if (ints[MHL_INT_RCHANGE] & MHL_INT_RC_DCAP_CHG) {
		switch (ctx->mode) {
		case CM_MHL3:
			sii8620_mt_read_xdevcap_reg(ctx, MHL_XDC_ECBUS_SPEEDS);
			sii8620_mt_set_cont(ctx, sii8620_got_ecbus_speed);
			break;
		case CM_ECBUS_S:
			sii8620_mt_read_devcap(ctx, true);
			break;
		default:
			break;
		}
	}
	if (ints[MHL_INT_RCHANGE] & MHL_INT_RC_FEAT_REQ)
		sii8620_send_features(ctx);
	if (ints[MHL_INT_RCHANGE] & MHL_INT_RC_FEAT_COMPLETE) {
		ctx->feature_complete = true;
		if (ctx->edid)
			sii8620_enable_hpd(ctx);
	}
}