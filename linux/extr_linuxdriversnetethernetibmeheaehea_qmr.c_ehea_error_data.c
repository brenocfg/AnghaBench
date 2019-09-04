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
struct ehea_adapter {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  EHEA_BMASK_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR_DATA_TYPE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long H_R_STATE ; 
 unsigned long H_SUCCESS ; 
 unsigned long ehea_h_error_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  print_error_data (int /*<<< orphan*/ *) ; 

u64 ehea_error_data(struct ehea_adapter *adapter, u64 res_handle,
		    u64 *aer, u64 *aerr)
{
	unsigned long ret;
	u64 *rblock;
	u64 type = 0;

	rblock = (void *)get_zeroed_page(GFP_KERNEL);
	if (!rblock) {
		pr_err("Cannot allocate rblock memory\n");
		goto out;
	}

	ret = ehea_h_error_data(adapter->handle, res_handle, rblock);

	if (ret == H_SUCCESS) {
		type = EHEA_BMASK_GET(ERROR_DATA_TYPE, rblock[2]);
		*aer = rblock[6];
		*aerr = rblock[12];
		print_error_data(rblock);
	} else if (ret == H_R_STATE) {
		pr_err("No error data available: %llX\n", res_handle);
	} else
		pr_err("Error data could not be fetched: %llX\n", res_handle);

	free_page((unsigned long)rblock);
out:
	return type;
}