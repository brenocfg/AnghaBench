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
typedef  int u32 ;
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 int BIT_DDMACH0_CHKSUM_CONT ; 
 int BIT_DDMACH0_CHKSUM_EN ; 
 int BIT_DDMACH0_OWN ; 
 int BIT_MASK_DDMACH0_DLEN ; 
 int EBUSY ; 
 int /*<<< orphan*/  REG_DDMA_CH0CTRL ; 
 int /*<<< orphan*/  check_hw_ready (struct rtw_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ iddma_enable (struct rtw_dev*,int,int,int) ; 

__attribute__((used)) static int iddma_download_firmware(struct rtw_dev *rtwdev, u32 src, u32 dst,
				   u32 len, u8 first)
{
	u32 ch0_ctrl = BIT_DDMACH0_CHKSUM_EN | BIT_DDMACH0_OWN;

	if (!check_hw_ready(rtwdev, REG_DDMA_CH0CTRL, BIT_DDMACH0_OWN, 0))
		return -EBUSY;

	ch0_ctrl |= len & BIT_MASK_DDMACH0_DLEN;
	if (!first)
		ch0_ctrl |= BIT_DDMACH0_CHKSUM_CONT;

	if (iddma_enable(rtwdev, src, dst, ch0_ctrl))
		return -EBUSY;

	return 0;
}