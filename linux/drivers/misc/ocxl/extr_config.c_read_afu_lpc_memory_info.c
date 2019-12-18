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
typedef  int u64 ;
typedef  unsigned long long u32 ;
typedef  int u16 ;
struct pci_dev {int dummy; } ;
struct ocxl_fn_config {int dummy; } ;
struct ocxl_afu_config {unsigned long long lpc_mem_offset; int lpc_mem_size; int special_purpose_mem_offset; int special_purpose_mem_size; } ;

/* Variables and functions */
 unsigned long long EXTRACT_BITS (unsigned long long,int /*<<< orphan*/ ,int) ; 
 scalar_t__ OCXL_DVSEC_TEMPL_ALL_MEM_SZ ; 
 scalar_t__ OCXL_DVSEC_TEMPL_LPC_MEM_START ; 
 scalar_t__ OCXL_DVSEC_TEMPL_LPC_MEM_SZ ; 
 int read_afu_info (struct pci_dev*,struct ocxl_fn_config*,scalar_t__,unsigned long long*) ; 
 int read_template_version (struct pci_dev*,struct ocxl_fn_config*,int*,int*) ; 

__attribute__((used)) static int read_afu_lpc_memory_info(struct pci_dev *dev,
				struct ocxl_fn_config *fn,
				struct ocxl_afu_config *afu)
{
	int rc;
	u32 val32;
	u16 templ_version;
	u16 templ_len;
	u64 total_mem_size = 0;
	u64 lpc_mem_size = 0;

	afu->lpc_mem_offset = 0;
	afu->lpc_mem_size = 0;
	afu->special_purpose_mem_offset = 0;
	afu->special_purpose_mem_size = 0;
	/*
	 * For AFUs following template v1.0, the LPC memory covers the
	 * total memory. Its size is a power of 2.
	 *
	 * For AFUs with template >= v1.01, the total memory size is
	 * still a power of 2, but it is split in 2 parts:
	 * - the LPC memory, whose size can now be anything
	 * - the remainder memory is a special purpose memory, whose
	 *   definition is AFU-dependent. It is not accessible through
	 *   the usual commands for LPC memory
	 */
	rc = read_afu_info(dev, fn, OCXL_DVSEC_TEMPL_ALL_MEM_SZ, &val32);
	if (rc)
		return rc;

	val32 = EXTRACT_BITS(val32, 0, 7);
	if (!val32)
		return 0; /* No LPC memory */

	/*
	 * The configuration space spec allows for a memory size of up
	 * to 2^255 bytes.
	 *
	 * Current generation hardware uses 56-bit physical addresses,
	 * but we won't be able to get near close to that, as we won't
	 * have a hole big enough in the memory map.  Let it pass in
	 * the driver for now. We'll get an error from the firmware
	 * when trying to configure something too big.
	 */
	total_mem_size = 1ull << val32;

	rc = read_afu_info(dev, fn, OCXL_DVSEC_TEMPL_LPC_MEM_START, &val32);
	if (rc)
		return rc;

	afu->lpc_mem_offset = val32;

	rc = read_afu_info(dev, fn, OCXL_DVSEC_TEMPL_LPC_MEM_START + 4, &val32);
	if (rc)
		return rc;

	afu->lpc_mem_offset |= (u64) val32 << 32;

	rc = read_template_version(dev, fn, &templ_len, &templ_version);
	if (rc)
		return rc;

	if (templ_version >= 0x0101) {
		rc = read_afu_info(dev, fn,
				OCXL_DVSEC_TEMPL_LPC_MEM_SZ, &val32);
		if (rc)
			return rc;
		lpc_mem_size = val32;

		rc = read_afu_info(dev, fn,
				OCXL_DVSEC_TEMPL_LPC_MEM_SZ + 4, &val32);
		if (rc)
			return rc;
		lpc_mem_size |= (u64) val32 << 32;
	} else {
		lpc_mem_size = total_mem_size;
	}
	afu->lpc_mem_size = lpc_mem_size;

	if (lpc_mem_size < total_mem_size) {
		afu->special_purpose_mem_offset =
			afu->lpc_mem_offset + lpc_mem_size;
		afu->special_purpose_mem_size =
			total_mem_size - lpc_mem_size;
	}
	return 0;
}