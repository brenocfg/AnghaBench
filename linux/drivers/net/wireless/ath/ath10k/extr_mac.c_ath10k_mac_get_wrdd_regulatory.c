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
typedef  int u32 ;
typedef  int u16 ;
struct ath10k {int /*<<< orphan*/  dev; } ;
struct acpi_buffer {int /*<<< orphan*/  pointer; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  acpi_string ;
typedef  char* acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (char*) ; 
 int /*<<< orphan*/  ACPI_HANDLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATH10K_DBG_BOOT ; 
 int COUNTRY_ERD_FLAG ; 
 int EIO ; 
 int EOPNOTSUPP ; 
 scalar_t__ WRD_METHOD ; 
 char* acpi_evaluate_object (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct acpi_buffer*) ; 
 char* acpi_get_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,char*) ; 
 int ath10k_mac_wrdd_get_mcc (struct ath10k*,int /*<<< orphan*/ ) ; 
 int ath_regd_find_country_by_name (char*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath10k_mac_get_wrdd_regulatory(struct ath10k *ar, u16 *rd)
{
	acpi_handle root_handle;
	acpi_handle handle;
	struct acpi_buffer wrdd = {ACPI_ALLOCATE_BUFFER, NULL};
	acpi_status status;
	u32 alpha2_code;
	char alpha2[3];

	root_handle = ACPI_HANDLE(ar->dev);
	if (!root_handle)
		return -EOPNOTSUPP;

	status = acpi_get_handle(root_handle, (acpi_string)WRD_METHOD, &handle);
	if (ACPI_FAILURE(status)) {
		ath10k_dbg(ar, ATH10K_DBG_BOOT,
			   "failed to get wrd method %d\n", status);
		return -EIO;
	}

	status = acpi_evaluate_object(handle, NULL, NULL, &wrdd);
	if (ACPI_FAILURE(status)) {
		ath10k_dbg(ar, ATH10K_DBG_BOOT,
			   "failed to call wrdc %d\n", status);
		return -EIO;
	}

	alpha2_code = ath10k_mac_wrdd_get_mcc(ar, wrdd.pointer);
	kfree(wrdd.pointer);
	if (!alpha2_code)
		return -EIO;

	alpha2[0] = (alpha2_code >> 8) & 0xff;
	alpha2[1] = (alpha2_code >> 0) & 0xff;
	alpha2[2] = '\0';

	ath10k_dbg(ar, ATH10K_DBG_BOOT,
		   "regulatory hint from WRDD (alpha2-code): %s\n", alpha2);

	*rd = ath_regd_find_country_by_name(alpha2);
	if (*rd == 0xffff)
		return -EIO;

	*rd |= COUNTRY_ERD_FLAG;
	return 0;
}