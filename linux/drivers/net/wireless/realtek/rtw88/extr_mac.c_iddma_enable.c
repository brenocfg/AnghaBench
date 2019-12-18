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
typedef  int /*<<< orphan*/  u32 ;
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_DDMACH0_OWN ; 
 int EBUSY ; 
 int /*<<< orphan*/  REG_DDMA_CH0CTRL ; 
 int /*<<< orphan*/  REG_DDMA_CH0DA ; 
 int /*<<< orphan*/  REG_DDMA_CH0SA ; 
 int /*<<< orphan*/  check_hw_ready (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write32 (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iddma_enable(struct rtw_dev *rtwdev, u32 src, u32 dst, u32 ctrl)
{
	rtw_write32(rtwdev, REG_DDMA_CH0SA, src);
	rtw_write32(rtwdev, REG_DDMA_CH0DA, dst);
	rtw_write32(rtwdev, REG_DDMA_CH0CTRL, ctrl);

	if (!check_hw_ready(rtwdev, REG_DDMA_CH0CTRL, BIT_DDMACH0_OWN, 0))
		return -EBUSY;

	return 0;
}