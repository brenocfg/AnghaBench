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
typedef  int u64 ;
typedef  int u32 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct cxl {TYPE_1__* native; } ;
struct TYPE_2__ {int no_data_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  CXL_PSL9_APCDEDALLOC ; 
 int /*<<< orphan*/  CXL_PSL9_APCDEDTYPE ; 
 int /*<<< orphan*/  CXL_PSL9_DEBUG ; 
 int /*<<< orphan*/  CXL_PSL9_DSNDCTL ; 
 int /*<<< orphan*/  CXL_PSL9_FIR_CNTL ; 
 int CXL_PSL_DEBUG_CDC ; 
 int /*<<< orphan*/  CXL_XSL9_DEF ; 
 int /*<<< orphan*/  CXL_XSL9_DSNCTL ; 
 int /*<<< orphan*/  CXL_XSL9_INV ; 
 int cxl_calc_capp_routing (struct pci_dev*,int*,int*,int*) ; 
 int cxl_get_xsl9_dsnctl (struct pci_dev*,int,int*) ; 
 int cxl_p1_read (struct cxl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxl_p1_write (struct cxl*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int init_implementation_adapter_regs_psl9(struct cxl *adapter,
						 struct pci_dev *dev)
{
	u64 xsl_dsnctl, psl_fircntl;
	u64 chipid;
	u32 phb_index;
	u64 capp_unit_id;
	u64 psl_debug;
	int rc;

	rc = cxl_calc_capp_routing(dev, &chipid, &phb_index, &capp_unit_id);
	if (rc)
		return rc;

	rc = cxl_get_xsl9_dsnctl(dev, capp_unit_id, &xsl_dsnctl);
	if (rc)
		return rc;

	cxl_p1_write(adapter, CXL_XSL9_DSNCTL, xsl_dsnctl);

	/* Set fir_cntl to recommended value for production env */
	psl_fircntl = (0x2ULL << (63-3)); /* ce_report */
	psl_fircntl |= (0x1ULL << (63-6)); /* FIR_report */
	psl_fircntl |= 0x1ULL; /* ce_thresh */
	cxl_p1_write(adapter, CXL_PSL9_FIR_CNTL, psl_fircntl);

	/* Setup the PSL to transmit packets on the PCIe before the
	 * CAPP is enabled. Make sure that CAPP virtual machines are disabled
	 */
	cxl_p1_write(adapter, CXL_PSL9_DSNDCTL, 0x0001001000012A10ULL);

	/*
	 * A response to an ASB_Notify request is returned by the
	 * system as an MMIO write to the address defined in
	 * the PSL_TNR_ADDR register.
	 * keep the Reset Value: 0x00020000E0000000
	 */

	/* Enable XSL rty limit */
	cxl_p1_write(adapter, CXL_XSL9_DEF, 0x51F8000000000005ULL);

	/* Change XSL_INV dummy read threshold */
	cxl_p1_write(adapter, CXL_XSL9_INV, 0x0000040007FFC200ULL);

	if (phb_index == 3) {
		/* disable machines 31-47 and 20-27 for DMA */
		cxl_p1_write(adapter, CXL_PSL9_APCDEDTYPE, 0x40000FF3FFFF0000ULL);
	}

	/* Snoop machines */
	cxl_p1_write(adapter, CXL_PSL9_APCDEDALLOC, 0x800F000200000000ULL);

	/* Enable NORST and DD2 features */
	cxl_p1_write(adapter, CXL_PSL9_DEBUG, 0xC000000000000000ULL);

	/*
	 * Check if PSL has data-cache. We need to flush adapter datacache
	 * when as its about to be removed.
	 */
	psl_debug = cxl_p1_read(adapter, CXL_PSL9_DEBUG);
	if (psl_debug & CXL_PSL_DEBUG_CDC) {
		dev_dbg(&dev->dev, "No data-cache present\n");
		adapter->native->no_data_cache = true;
	}

	return 0;
}