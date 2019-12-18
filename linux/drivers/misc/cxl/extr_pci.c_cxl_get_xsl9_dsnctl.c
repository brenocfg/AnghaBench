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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ get_phb_indications (struct pci_dev*,int*,int*,int*) ; 

int cxl_get_xsl9_dsnctl(struct pci_dev *dev, u64 capp_unit_id, u64 *reg)
{
	u64 xsl_dsnctl;
	u64 capiind, asnind, nbwind;

	/*
	 * CAPI Identifier bits [0:7]
	 * bit 61:60 MSI bits --> 0
	 * bit 59 TVT selector --> 0
	 */
	if (get_phb_indications(dev, &capiind, &asnind, &nbwind))
		return -ENODEV;

	/*
	 * Tell XSL where to route data to.
	 * The field chipid should match the PHB CAPI_CMPM register
	 */
	xsl_dsnctl = (capiind << (63-15)); /* Bit 57 */
	xsl_dsnctl |= (capp_unit_id << (63-15));

	/* nMMU_ID Defaults to: b’000001001’*/
	xsl_dsnctl |= ((u64)0x09 << (63-28));

	/*
	 * Used to identify CAPI packets which should be sorted into
	 * the Non-Blocking queues by the PHB. This field should match
	 * the PHB PBL_NBW_CMPM register
	 * nbwind=0x03, bits [57:58], must include capi indicator.
	 * Not supported on P9 DD1.
	 */
	xsl_dsnctl |= (nbwind << (63-55));

	/*
	 * Upper 16b address bits of ASB_Notify messages sent to the
	 * system. Need to match the PHB’s ASN Compare/Mask Register.
	 * Not supported on P9 DD1.
	 */
	xsl_dsnctl |= asnind;

	*reg = xsl_dsnctl;
	return 0;
}