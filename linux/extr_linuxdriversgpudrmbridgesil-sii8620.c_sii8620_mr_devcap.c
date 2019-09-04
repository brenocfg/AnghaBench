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
struct sii8620 {scalar_t__ error; int devcap_read; int /*<<< orphan*/  devcap; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 size_t MHL_DCAP_ADOPTER_ID_H ; 
 size_t MHL_DCAP_ADOPTER_ID_L ; 
 size_t MHL_DCAP_DEVICE_ID_H ; 
 size_t MHL_DCAP_DEVICE_ID_L ; 
 size_t MHL_DCAP_MHL_VERSION ; 
 int MHL_DCAP_SIZE ; 
 int /*<<< orphan*/  REG_EDID_FIFO_RD_DATA ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  sii8620_identify_sink (struct sii8620*) ; 
 int /*<<< orphan*/  sii8620_read_buf (struct sii8620*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  sii8620_update_array (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void sii8620_mr_devcap(struct sii8620 *ctx)
{
	u8 dcap[MHL_DCAP_SIZE];
	struct device *dev = ctx->dev;

	sii8620_read_buf(ctx, REG_EDID_FIFO_RD_DATA, dcap, MHL_DCAP_SIZE);
	if (ctx->error < 0)
		return;

	dev_info(dev, "detected dongle MHL %d.%d, ChipID %02x%02x:%02x%02x\n",
		 dcap[MHL_DCAP_MHL_VERSION] / 16,
		 dcap[MHL_DCAP_MHL_VERSION] % 16,
		 dcap[MHL_DCAP_ADOPTER_ID_H], dcap[MHL_DCAP_ADOPTER_ID_L],
		 dcap[MHL_DCAP_DEVICE_ID_H], dcap[MHL_DCAP_DEVICE_ID_L]);
	sii8620_update_array(ctx->devcap, dcap, MHL_DCAP_SIZE);
	ctx->devcap_read = true;
	sii8620_identify_sink(ctx);
}