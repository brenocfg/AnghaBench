#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct rtw_dev {struct rtw_chip_info* chip; } ;
struct rtw_chip_info {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* coex_set_ant_switch ) (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline
void rtw_coex_set_ant_switch(struct rtw_dev *rtwdev, u8 ctrl_type, u8 pos_type)
{
	struct rtw_chip_info *chip = rtwdev->chip;

	if (!chip->ops->coex_set_ant_switch)
		return;

	chip->ops->coex_set_ant_switch(rtwdev, ctrl_type, pos_type);
}