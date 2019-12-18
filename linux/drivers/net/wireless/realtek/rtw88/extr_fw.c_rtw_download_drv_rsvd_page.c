#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {int rsvd_drv_pg_num; int /*<<< orphan*/  rsvd_drv_addr; } ;
struct rtw_dev {TYPE_2__ fifo; TYPE_1__* chip; } ;
struct TYPE_3__ {int page_size; } ;

/* Variables and functions */
 int ENOMEM ; 
 int rtw_fw_write_data_rsvd_page (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int rtw_download_drv_rsvd_page(struct rtw_dev *rtwdev, u8 *buf, u32 size)
{
	u32 pg_size;
	u32 pg_num = 0;
	u16 pg_addr = 0;

	pg_size = rtwdev->chip->page_size;
	pg_num = size / pg_size + ((size & (pg_size - 1)) ? 1 : 0);
	if (pg_num > rtwdev->fifo.rsvd_drv_pg_num)
		return -ENOMEM;

	pg_addr = rtwdev->fifo.rsvd_drv_addr;

	return rtw_fw_write_data_rsvd_page(rtwdev, pg_addr, buf, size);
}