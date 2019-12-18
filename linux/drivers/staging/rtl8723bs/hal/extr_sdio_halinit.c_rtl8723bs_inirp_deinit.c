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
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_hci_hal_init_c_ ; 

__attribute__((used)) static u32 rtl8723bs_inirp_deinit(struct adapter *padapter)
{
	RT_TRACE(_module_hci_hal_init_c_, _drv_info_, ("+rtl8723bs_inirp_deinit\n"));

	RT_TRACE(_module_hci_hal_init_c_, _drv_info_, ("-rtl8723bs_inirp_deinit\n"));

	return _SUCCESS;
}