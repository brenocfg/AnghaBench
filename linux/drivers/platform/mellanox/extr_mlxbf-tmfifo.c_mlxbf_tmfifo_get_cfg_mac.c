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
typedef  scalar_t__ efi_status_t ;
typedef  int /*<<< orphan*/  efi_guid_t ;
struct TYPE_2__ {scalar_t__ (* get_variable ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EFI_GLOBAL_VARIABLE_GUID ; 
 scalar_t__ EFI_SUCCESS ; 
 int ETH_ALEN ; 
 TYPE_1__ efi ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxbf_tmfifo_efi_name ; 
 int /*<<< orphan*/ * mlxbf_tmfifo_net_default_mac ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlxbf_tmfifo_get_cfg_mac(u8 *mac)
{
	efi_guid_t guid = EFI_GLOBAL_VARIABLE_GUID;
	unsigned long size = ETH_ALEN;
	u8 buf[ETH_ALEN];
	efi_status_t rc;

	rc = efi.get_variable(mlxbf_tmfifo_efi_name, &guid, NULL, &size, buf);
	if (rc == EFI_SUCCESS && size == ETH_ALEN)
		ether_addr_copy(mac, buf);
	else
		ether_addr_copy(mac, mlxbf_tmfifo_net_default_mac);
}