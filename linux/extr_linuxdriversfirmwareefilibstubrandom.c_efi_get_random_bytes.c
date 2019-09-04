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
struct efi_rng_protocol {scalar_t__ (* get_rng ) (struct efi_rng_protocol*,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  efi_system_table_t ;
typedef  scalar_t__ efi_status_t ;
typedef  int /*<<< orphan*/  efi_guid_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFI_RNG_PROTOCOL_GUID ; 
 scalar_t__ EFI_SUCCESS ; 
 scalar_t__ efi_call_early (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  locate_protocol ; 
 scalar_t__ stub1 (struct efi_rng_protocol*,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ *) ; 

efi_status_t efi_get_random_bytes(efi_system_table_t *sys_table_arg,
				  unsigned long size, u8 *out)
{
	efi_guid_t rng_proto = EFI_RNG_PROTOCOL_GUID;
	efi_status_t status;
	struct efi_rng_protocol *rng;

	status = efi_call_early(locate_protocol, &rng_proto, NULL,
				(void **)&rng);
	if (status != EFI_SUCCESS)
		return status;

	return rng->get_rng(rng, NULL, size, out);
}