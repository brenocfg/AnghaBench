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
typedef  size_t u32 ;
struct stepping_info {int /*<<< orphan*/  stepping; } ;
struct intel_package_header {int header_ver; int header_len; size_t num_entries; } ;
struct intel_fw_info {int dummy; } ;
struct intel_csr {int dummy; } ;

/* Variables and functions */
 size_t CSR_DEFAULT_FW_OFFSET ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 size_t PACKAGE_MAX_FW_INFO_ENTRIES ; 
 size_t PACKAGE_V2_MAX_FW_INFO_ENTRIES ; 
 scalar_t__ WARN_ON (int) ; 
 size_t find_dmc_fw_offset (struct intel_fw_info const*,size_t,struct stepping_info const*,int) ; 

__attribute__((used)) static u32
parse_csr_fw_package(struct intel_csr *csr,
		     const struct intel_package_header *package_header,
		     const struct stepping_info *si,
		     size_t rem_size)
{
	u32 package_size = sizeof(struct intel_package_header);
	u32 num_entries, max_entries, dmc_offset;
	const struct intel_fw_info *fw_info;

	if (rem_size < package_size)
		goto error_truncated;

	if (package_header->header_ver == 1) {
		max_entries = PACKAGE_MAX_FW_INFO_ENTRIES;
	} else if (package_header->header_ver == 2) {
		max_entries = PACKAGE_V2_MAX_FW_INFO_ENTRIES;
	} else {
		DRM_ERROR("DMC firmware has unknown header version %u\n",
			  package_header->header_ver);
		return 0;
	}

	/*
	 * We should always have space for max_entries,
	 * even if not all are used
	 */
	package_size += max_entries * sizeof(struct intel_fw_info);
	if (rem_size < package_size)
		goto error_truncated;

	if (package_header->header_len * 4 != package_size) {
		DRM_ERROR("DMC firmware has wrong package header length "
			  "(%u bytes)\n", package_size);
		return 0;
	}

	num_entries = package_header->num_entries;
	if (WARN_ON(package_header->num_entries > max_entries))
		num_entries = max_entries;

	fw_info = (const struct intel_fw_info *)
		((u8 *)package_header + sizeof(*package_header));
	dmc_offset = find_dmc_fw_offset(fw_info, num_entries, si,
					package_header->header_ver);
	if (dmc_offset == CSR_DEFAULT_FW_OFFSET) {
		DRM_ERROR("DMC firmware not supported for %c stepping\n",
			  si->stepping);
		return 0;
	}

	/* dmc_offset is in dwords */
	return package_size + dmc_offset * 4;

error_truncated:
	DRM_ERROR("Truncated DMC firmware, refusing.\n");
	return 0;
}