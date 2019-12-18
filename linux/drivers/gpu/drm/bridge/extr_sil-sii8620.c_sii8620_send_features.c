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
typedef  int /*<<< orphan*/  u8 ;
struct sii8620 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int BIT_MDT_XMIT_CTRL_EN ; 
 int BIT_MDT_XMIT_CTRL_FIXED_BURST_LEN ; 
 int /*<<< orphan*/  MHL_BURST_ID_HID_PAYLOAD ; 
 int /*<<< orphan*/  REG_MDT_XMIT_CTRL ; 
 int /*<<< orphan*/  REG_MDT_XMIT_WRITE_PORT ; 
 int /*<<< orphan*/  sii8620_mhl_burst_emsc_support_set (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sii8620_write (struct sii8620*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sii8620_write_buf (struct sii8620*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sii8620_send_features(struct sii8620 *ctx)
{
	u8 buf[16];

	sii8620_write(ctx, REG_MDT_XMIT_CTRL, BIT_MDT_XMIT_CTRL_EN
		| BIT_MDT_XMIT_CTRL_FIXED_BURST_LEN);
	sii8620_mhl_burst_emsc_support_set((void *)buf,
		MHL_BURST_ID_HID_PAYLOAD);
	sii8620_write_buf(ctx, REG_MDT_XMIT_WRITE_PORT, buf, ARRAY_SIZE(buf));
}