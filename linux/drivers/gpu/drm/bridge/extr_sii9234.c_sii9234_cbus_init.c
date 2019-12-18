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
struct sii9234 {int dummy; } ;

/* Variables and functions */
 int CBUS_DEVCAP_OFFSET ; 
 int CBUS_INTR1_ENABLE_REG ; 
 int CBUS_INTR2_ENABLE_REG ; 
 int MHL_DCAP_ADOPTER_ID_H ; 
 int MHL_DCAP_ADOPTER_ID_L ; 
 int MHL_DCAP_BANDWIDTH ; 
 int MHL_DCAP_CAT ; 
 int MHL_DCAP_CAT_SOURCE ; 
 int MHL_DCAP_DEVICE_ID_H ; 
 int MHL_DCAP_DEVICE_ID_L ; 
 int MHL_DCAP_DEV_STATE ; 
 int MHL_DCAP_FEATURE_FLAG ; 
 int MHL_DCAP_FEATURE_RAP_SUPPORT ; 
 int MHL_DCAP_FEATURE_RCP_SUPPORT ; 
 int MHL_DCAP_FEATURE_SP_SUPPORT ; 
 int MHL_DCAP_INT_STAT_SIZE ; 
 int MHL_DCAP_LD_GUI ; 
 int MHL_DCAP_LOG_DEV_MAP ; 
 int MHL_DCAP_MHL_VERSION ; 
 int MHL_DCAP_RESERVED ; 
 int MHL_DCAP_SCRATCHPAD_SIZE ; 
 int MHL_DCAP_VIDEO_TYPE ; 
 int MHL_DCAP_VID_LINK_MODE ; 
 int MHL_DCAP_VID_LINK_RGB444 ; 
 int MHL_DCAP_VID_LINK_YCBCR444 ; 
 int MHL_DCAP_VT_GRAPHICS ; 
 int SII9234_INT_STAT_SIZE ; 
 int SII9234_MHL_VERSION ; 
 int SII9234_SCRATCHPAD_SIZE ; 
 int /*<<< orphan*/  cbus_writeb (struct sii9234*,int,int) ; 
 int /*<<< orphan*/  cbus_writebm (struct sii9234*,int,int,int) ; 
 int sii9234_clear_error (struct sii9234*) ; 

__attribute__((used)) static int sii9234_cbus_init(struct sii9234 *ctx)
{
	cbus_writeb(ctx, 0x07, 0xF2);
	cbus_writeb(ctx, 0x40, 0x03);
	cbus_writeb(ctx, 0x42, 0x06);
	cbus_writeb(ctx, 0x36, 0x0C);
	cbus_writeb(ctx, 0x3D, 0xFD);
	cbus_writeb(ctx, 0x1C, 0x01);
	cbus_writeb(ctx, 0x1D, 0x0F);
	cbus_writeb(ctx, 0x44, 0x02);
	/* Setup our devcap */
	cbus_writeb(ctx, CBUS_DEVCAP_OFFSET + MHL_DCAP_DEV_STATE, 0x00);
	cbus_writeb(ctx, CBUS_DEVCAP_OFFSET + MHL_DCAP_MHL_VERSION,
		    SII9234_MHL_VERSION);
	cbus_writeb(ctx, CBUS_DEVCAP_OFFSET + MHL_DCAP_CAT,
		    MHL_DCAP_CAT_SOURCE);
	cbus_writeb(ctx, CBUS_DEVCAP_OFFSET + MHL_DCAP_ADOPTER_ID_H, 0x01);
	cbus_writeb(ctx, CBUS_DEVCAP_OFFSET + MHL_DCAP_ADOPTER_ID_L, 0x41);
	cbus_writeb(ctx, CBUS_DEVCAP_OFFSET + MHL_DCAP_VID_LINK_MODE,
		    MHL_DCAP_VID_LINK_RGB444 | MHL_DCAP_VID_LINK_YCBCR444);
	cbus_writeb(ctx, CBUS_DEVCAP_OFFSET + MHL_DCAP_VIDEO_TYPE,
		    MHL_DCAP_VT_GRAPHICS);
	cbus_writeb(ctx, CBUS_DEVCAP_OFFSET + MHL_DCAP_LOG_DEV_MAP,
		    MHL_DCAP_LD_GUI);
	cbus_writeb(ctx, CBUS_DEVCAP_OFFSET + MHL_DCAP_BANDWIDTH, 0x0F);
	cbus_writeb(ctx, CBUS_DEVCAP_OFFSET + MHL_DCAP_FEATURE_FLAG,
		    MHL_DCAP_FEATURE_RCP_SUPPORT | MHL_DCAP_FEATURE_RAP_SUPPORT
			| MHL_DCAP_FEATURE_SP_SUPPORT);
	cbus_writeb(ctx, CBUS_DEVCAP_OFFSET + MHL_DCAP_DEVICE_ID_H, 0x0);
	cbus_writeb(ctx, CBUS_DEVCAP_OFFSET + MHL_DCAP_DEVICE_ID_L, 0x0);
	cbus_writeb(ctx, CBUS_DEVCAP_OFFSET + MHL_DCAP_SCRATCHPAD_SIZE,
		    SII9234_SCRATCHPAD_SIZE);
	cbus_writeb(ctx, CBUS_DEVCAP_OFFSET + MHL_DCAP_INT_STAT_SIZE,
		    SII9234_INT_STAT_SIZE);
	cbus_writeb(ctx, CBUS_DEVCAP_OFFSET + MHL_DCAP_RESERVED, 0);
	cbus_writebm(ctx, 0x31, 0x0C, 0x0C);
	cbus_writeb(ctx, 0x30, 0x01);
	cbus_writebm(ctx, 0x3C, 0x30, 0x38);
	cbus_writebm(ctx, 0x22, 0x0D, 0x0F);
	cbus_writebm(ctx, 0x2E, 0x15, 0x15);
	cbus_writeb(ctx, CBUS_INTR1_ENABLE_REG, 0);
	cbus_writeb(ctx, CBUS_INTR2_ENABLE_REG, 0);

	return sii9234_clear_error(ctx);
}