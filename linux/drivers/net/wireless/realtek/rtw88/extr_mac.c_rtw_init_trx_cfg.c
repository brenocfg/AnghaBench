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
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 int init_h2c (struct rtw_dev*) ; 
 int priority_queue_cfg (struct rtw_dev*) ; 
 int txdma_queue_mapping (struct rtw_dev*) ; 

__attribute__((used)) static int rtw_init_trx_cfg(struct rtw_dev *rtwdev)
{
	int ret;

	ret = txdma_queue_mapping(rtwdev);
	if (ret)
		return ret;

	ret = priority_queue_cfg(rtwdev);
	if (ret)
		return ret;

	ret = init_h2c(rtwdev);
	if (ret)
		return ret;

	return 0;
}