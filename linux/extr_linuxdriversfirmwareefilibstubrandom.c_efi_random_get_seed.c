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
struct linux_efi_random_seed {int /*<<< orphan*/  size; int /*<<< orphan*/  bits; } ;
struct efi_rng_protocol {scalar_t__ (* get_rng ) (struct efi_rng_protocol*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  efi_system_table_t ;
typedef  scalar_t__ efi_status_t ;
typedef  int /*<<< orphan*/  efi_guid_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFI_RANDOM_SEED_SIZE ; 
 int /*<<< orphan*/  EFI_RNG_ALGORITHM_RAW ; 
 int /*<<< orphan*/  EFI_RNG_PROTOCOL_GUID ; 
 int /*<<< orphan*/  EFI_RUNTIME_SERVICES_DATA ; 
 scalar_t__ EFI_SUCCESS ; 
 scalar_t__ EFI_UNSUPPORTED ; 
 int /*<<< orphan*/  LINUX_EFI_RANDOM_SEED_TABLE_GUID ; 
 int /*<<< orphan*/  allocate_pool ; 
 scalar_t__ efi_call_early (int /*<<< orphan*/ ,struct linux_efi_random_seed*,...) ; 
 int /*<<< orphan*/  free_pool ; 
 int /*<<< orphan*/  install_configuration_table ; 
 int /*<<< orphan*/  locate_protocol ; 
 scalar_t__ stub1 (struct efi_rng_protocol*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (struct efi_rng_protocol*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

efi_status_t efi_random_get_seed(efi_system_table_t *sys_table_arg)
{
	efi_guid_t rng_proto = EFI_RNG_PROTOCOL_GUID;
	efi_guid_t rng_algo_raw = EFI_RNG_ALGORITHM_RAW;
	efi_guid_t rng_table_guid = LINUX_EFI_RANDOM_SEED_TABLE_GUID;
	struct efi_rng_protocol *rng;
	struct linux_efi_random_seed *seed;
	efi_status_t status;

	status = efi_call_early(locate_protocol, &rng_proto, NULL,
				(void **)&rng);
	if (status != EFI_SUCCESS)
		return status;

	status = efi_call_early(allocate_pool, EFI_RUNTIME_SERVICES_DATA,
				sizeof(*seed) + EFI_RANDOM_SEED_SIZE,
				(void **)&seed);
	if (status != EFI_SUCCESS)
		return status;

	status = rng->get_rng(rng, &rng_algo_raw, EFI_RANDOM_SEED_SIZE,
			      seed->bits);
	if (status == EFI_UNSUPPORTED)
		/*
		 * Use whatever algorithm we have available if the raw algorithm
		 * is not implemented.
		 */
		status = rng->get_rng(rng, NULL, EFI_RANDOM_SEED_SIZE,
				      seed->bits);

	if (status != EFI_SUCCESS)
		goto err_freepool;

	seed->size = EFI_RANDOM_SEED_SIZE;
	status = efi_call_early(install_configuration_table, &rng_table_guid,
				seed);
	if (status != EFI_SUCCESS)
		goto err_freepool;

	return EFI_SUCCESS;

err_freepool:
	efi_call_early(free_pool, seed);
	return status;
}