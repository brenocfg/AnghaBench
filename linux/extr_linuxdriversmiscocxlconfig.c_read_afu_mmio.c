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
typedef  void* u32 ;
struct pci_dev {int dummy; } ;
struct ocxl_fn_config {int dummy; } ;
struct ocxl_afu_config {int global_mmio_bar; int global_mmio_offset; int pp_mmio_bar; int pp_mmio_offset; void* pp_mmio_stride; void* global_mmio_size; } ;

/* Variables and functions */
 int EXTRACT_BITS (void*,int,int) ; 
 scalar_t__ OCXL_DVSEC_TEMPL_MMIO_GLOBAL ; 
 scalar_t__ OCXL_DVSEC_TEMPL_MMIO_GLOBAL_SZ ; 
 scalar_t__ OCXL_DVSEC_TEMPL_MMIO_PP ; 
 scalar_t__ OCXL_DVSEC_TEMPL_MMIO_PP_SZ ; 
 int read_afu_info (struct pci_dev*,struct ocxl_fn_config*,scalar_t__,void**) ; 

__attribute__((used)) static int read_afu_mmio(struct pci_dev *dev, struct ocxl_fn_config *fn,
			struct ocxl_afu_config *afu)
{
	int rc;
	u32 val;

	/*
	 * Global MMIO
	 */
	rc = read_afu_info(dev, fn, OCXL_DVSEC_TEMPL_MMIO_GLOBAL, &val);
	if (rc)
		return rc;
	afu->global_mmio_bar = EXTRACT_BITS(val, 0, 2);
	afu->global_mmio_offset = EXTRACT_BITS(val, 16, 31) << 16;

	rc = read_afu_info(dev, fn, OCXL_DVSEC_TEMPL_MMIO_GLOBAL + 4, &val);
	if (rc)
		return rc;
	afu->global_mmio_offset += (u64) val << 32;

	rc = read_afu_info(dev, fn, OCXL_DVSEC_TEMPL_MMIO_GLOBAL_SZ, &val);
	if (rc)
		return rc;
	afu->global_mmio_size = val;

	/*
	 * Per-process MMIO
	 */
	rc = read_afu_info(dev, fn, OCXL_DVSEC_TEMPL_MMIO_PP, &val);
	if (rc)
		return rc;
	afu->pp_mmio_bar = EXTRACT_BITS(val, 0, 2);
	afu->pp_mmio_offset = EXTRACT_BITS(val, 16, 31) << 16;

	rc = read_afu_info(dev, fn, OCXL_DVSEC_TEMPL_MMIO_PP + 4, &val);
	if (rc)
		return rc;
	afu->pp_mmio_offset += (u64) val << 32;

	rc = read_afu_info(dev, fn, OCXL_DVSEC_TEMPL_MMIO_PP_SZ, &val);
	if (rc)
		return rc;
	afu->pp_mmio_stride = val;

	return 0;
}