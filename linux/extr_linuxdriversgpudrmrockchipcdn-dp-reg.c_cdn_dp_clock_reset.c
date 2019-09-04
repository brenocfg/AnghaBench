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
typedef  int u32 ;
struct cdn_dp_device {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ APB_INT_MASK ; 
 int CFG_DPTX_VIF_CLK_EN ; 
 int CFG_DPTX_VIF_CLK_RSTN_EN ; 
 int DPTX_FRMR_DATA_CLK_EN ; 
 int DPTX_FRMR_DATA_CLK_RSTN_EN ; 
 int DPTX_PHY_CHAR_CLK_EN ; 
 int DPTX_PHY_CHAR_RSTN_EN ; 
 int DPTX_PHY_DATA_CLK_EN ; 
 int DPTX_PHY_DATA_RSTN_EN ; 
 int DPTX_SYS_CLK_EN ; 
 int DPTX_SYS_CLK_RSTN_EN ; 
 scalar_t__ SOURCE_AIF_CAR ; 
 int SOURCE_AIF_CLK_EN ; 
 int SOURCE_AIF_CLK_RSTN_EN ; 
 int SOURCE_AIF_SYS_CLK_EN ; 
 int SOURCE_AIF_SYS_RSTN_EN ; 
 int SOURCE_AUX_SYS_CLK_EN ; 
 int SOURCE_AUX_SYS_CLK_RSTN_EN ; 
 scalar_t__ SOURCE_CIPHER_CAR ; 
 int SOURCE_CIPHER_CHAR_CLK_EN ; 
 int SOURCE_CIPHER_CHAR_CLK_RSTN_EN ; 
 int SOURCE_CIPHER_SYSTEM_CLK_RSTN_EN ; 
 int SOURCE_CIPHER_SYS_CLK_EN ; 
 scalar_t__ SOURCE_CRYPTO_CAR ; 
 int SOURCE_CRYPTO_SYS_CLK_EN ; 
 int SOURCE_CRYPTO_SYS_CLK_RSTN_EN ; 
 scalar_t__ SOURCE_DPTX_CAR ; 
 scalar_t__ SOURCE_PHY_CAR ; 
 int SOURCE_PHY_CLK_EN ; 
 int SOURCE_PHY_RSTN_EN ; 
 scalar_t__ SOURCE_PKT_CAR ; 
 int SOURCE_PKT_DATA_CLK_EN ; 
 int SOURCE_PKT_DATA_RSTN_EN ; 
 int SOURCE_PKT_SYS_CLK_EN ; 
 int SOURCE_PKT_SYS_RSTN_EN ; 
 int SPDIF_CDR_CLK_EN ; 
 int SPDIF_CDR_CLK_RSTN_EN ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void cdn_dp_clock_reset(struct cdn_dp_device *dp)
{
	u32 val;

	val = DPTX_FRMR_DATA_CLK_RSTN_EN |
	      DPTX_FRMR_DATA_CLK_EN |
	      DPTX_PHY_DATA_RSTN_EN |
	      DPTX_PHY_DATA_CLK_EN |
	      DPTX_PHY_CHAR_RSTN_EN |
	      DPTX_PHY_CHAR_CLK_EN |
	      SOURCE_AUX_SYS_CLK_RSTN_EN |
	      SOURCE_AUX_SYS_CLK_EN |
	      DPTX_SYS_CLK_RSTN_EN |
	      DPTX_SYS_CLK_EN |
	      CFG_DPTX_VIF_CLK_RSTN_EN |
	      CFG_DPTX_VIF_CLK_EN;
	writel(val, dp->regs + SOURCE_DPTX_CAR);

	val = SOURCE_PHY_RSTN_EN | SOURCE_PHY_CLK_EN;
	writel(val, dp->regs + SOURCE_PHY_CAR);

	val = SOURCE_PKT_SYS_RSTN_EN |
	      SOURCE_PKT_SYS_CLK_EN |
	      SOURCE_PKT_DATA_RSTN_EN |
	      SOURCE_PKT_DATA_CLK_EN;
	writel(val, dp->regs + SOURCE_PKT_CAR);

	val = SPDIF_CDR_CLK_RSTN_EN |
	      SPDIF_CDR_CLK_EN |
	      SOURCE_AIF_SYS_RSTN_EN |
	      SOURCE_AIF_SYS_CLK_EN |
	      SOURCE_AIF_CLK_RSTN_EN |
	      SOURCE_AIF_CLK_EN;
	writel(val, dp->regs + SOURCE_AIF_CAR);

	val = SOURCE_CIPHER_SYSTEM_CLK_RSTN_EN |
	      SOURCE_CIPHER_SYS_CLK_EN |
	      SOURCE_CIPHER_CHAR_CLK_RSTN_EN |
	      SOURCE_CIPHER_CHAR_CLK_EN;
	writel(val, dp->regs + SOURCE_CIPHER_CAR);

	val = SOURCE_CRYPTO_SYS_CLK_RSTN_EN |
	      SOURCE_CRYPTO_SYS_CLK_EN;
	writel(val, dp->regs + SOURCE_CRYPTO_CAR);

	/* enable Mailbox and PIF interrupt */
	writel(0, dp->regs + APB_INT_MASK);
}