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
typedef  unsigned long u64 ;
typedef  int u32 ;
typedef  scalar_t__ efi_status_t ;
typedef  int /*<<< orphan*/  efi_char16_t ;
struct TYPE_2__ {scalar_t__ (* query_variable_info ) (int,unsigned long*,unsigned long*,unsigned long*) ;scalar_t__ (* set_variable ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,unsigned long,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EFI_DUMMY_GUID ; 
 unsigned long EFI_MIN_RESERVE ; 
 scalar_t__ EFI_OUT_OF_RESOURCES ; 
 scalar_t__ EFI_SUCCESS ; 
 int EFI_VARIABLE_BOOTSERVICE_ACCESS ; 
 int EFI_VARIABLE_NON_VOLATILE ; 
 int EFI_VARIABLE_RUNTIME_ACCESS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__ efi ; 
 int /*<<< orphan*/  efi_delete_dummy_variable () ; 
 scalar_t__ efi_dummy_name ; 
 int /*<<< orphan*/  efi_no_storage_paranoia ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kzalloc (unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ query_variable_store_nonblocking (int,unsigned long) ; 
 scalar_t__ stub1 (int,unsigned long*,unsigned long*,unsigned long*) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,unsigned long,void*) ; 
 scalar_t__ stub3 (int,unsigned long*,unsigned long*,unsigned long*) ; 

efi_status_t efi_query_variable_store(u32 attributes, unsigned long size,
				      bool nonblocking)
{
	efi_status_t status;
	u64 storage_size, remaining_size, max_size;

	if (!(attributes & EFI_VARIABLE_NON_VOLATILE))
		return 0;

	if (nonblocking)
		return query_variable_store_nonblocking(attributes, size);

	status = efi.query_variable_info(attributes, &storage_size,
					 &remaining_size, &max_size);
	if (status != EFI_SUCCESS)
		return status;

	/*
	 * We account for that by refusing the write if permitting it would
	 * reduce the available space to under 5KB. This figure was provided by
	 * Samsung, so should be safe.
	 */
	if ((remaining_size - size < EFI_MIN_RESERVE) &&
		!efi_no_storage_paranoia) {

		/*
		 * Triggering garbage collection may require that the firmware
		 * generate a real EFI_OUT_OF_RESOURCES error. We can force
		 * that by attempting to use more space than is available.
		 */
		unsigned long dummy_size = remaining_size + 1024;
		void *dummy = kzalloc(dummy_size, GFP_KERNEL);

		if (!dummy)
			return EFI_OUT_OF_RESOURCES;

		status = efi.set_variable((efi_char16_t *)efi_dummy_name,
					  &EFI_DUMMY_GUID,
					  EFI_VARIABLE_NON_VOLATILE |
					  EFI_VARIABLE_BOOTSERVICE_ACCESS |
					  EFI_VARIABLE_RUNTIME_ACCESS,
					  dummy_size, dummy);

		if (status == EFI_SUCCESS) {
			/*
			 * This should have failed, so if it didn't make sure
			 * that we delete it...
			 */
			efi_delete_dummy_variable();
		}

		kfree(dummy);

		/*
		 * The runtime code may now have triggered a garbage collection
		 * run, so check the variable info again
		 */
		status = efi.query_variable_info(attributes, &storage_size,
						 &remaining_size, &max_size);

		if (status != EFI_SUCCESS)
			return status;

		/*
		 * There still isn't enough room, so return an error
		 */
		if (remaining_size - size < EFI_MIN_RESERVE)
			return EFI_OUT_OF_RESOURCES;
	}

	return EFI_SUCCESS;
}