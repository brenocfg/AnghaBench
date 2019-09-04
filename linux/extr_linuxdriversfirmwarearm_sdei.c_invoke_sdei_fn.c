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
typedef  int /*<<< orphan*/  u64 ;
struct arm_smccc_res {int /*<<< orphan*/  a0; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  SDEI_NOT_SUPPORTED ; 
 int /*<<< orphan*/  sdei_firmware_call (unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,struct arm_smccc_res*) ; 
 scalar_t__ sdei_is_err (struct arm_smccc_res*) ; 
 int sdei_to_linux_errno (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int invoke_sdei_fn(unsigned long function_id, unsigned long arg0,
			  unsigned long arg1, unsigned long arg2,
			  unsigned long arg3, unsigned long arg4,
			  u64 *result)
{
	int err = 0;
	struct arm_smccc_res res;

	if (sdei_firmware_call) {
		sdei_firmware_call(function_id, arg0, arg1, arg2, arg3, arg4,
				   &res);
		if (sdei_is_err(&res))
			err = sdei_to_linux_errno(res.a0);
	} else {
		/*
		 * !sdei_firmware_call means we failed to probe or called
		 * sdei_mark_interface_broken(). -EIO is not an error returned
		 * by sdei_to_linux_errno() and is used to suppress messages
		 * from this driver.
		 */
		err = -EIO;
		res.a0 = SDEI_NOT_SUPPORTED;
	}

	if (result)
		*result = res.a0;

	return err;
}