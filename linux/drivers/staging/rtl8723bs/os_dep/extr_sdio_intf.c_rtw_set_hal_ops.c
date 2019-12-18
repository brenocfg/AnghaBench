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
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtl8723bs_set_hal_ops (struct adapter*) ; 
 int /*<<< orphan*/  rtw_hal_data_init (struct adapter*) ; 

void rtw_set_hal_ops(struct adapter *padapter)
{
	/* alloc memory for HAL DATA */
	rtw_hal_data_init(padapter);

	rtl8723bs_set_hal_ops(padapter);
}