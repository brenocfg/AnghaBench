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
typedef  enum vpss_ccdc_source_sel { ____Placeholder_vpss_ccdc_source_sel } vpss_ccdc_source_sel ;

/* Variables and functions */
 int CCD_SRC_SEL_MASK ; 
 int CCD_SRC_SEL_SHIFT ; 
 int /*<<< orphan*/  DM365_ISP5_CCDCMUX ; 
 int VPSS_CCDCPG ; 
 int VPSS_PGLPBK ; 
 int isp5_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp5_write (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dm365_select_ccdc_source(enum vpss_ccdc_source_sel src_sel)
{
	u32 temp = isp5_read(DM365_ISP5_CCDCMUX) & ~CCD_SRC_SEL_MASK;

	/* if we are using pattern generator, enable it */
	if (src_sel == VPSS_PGLPBK || src_sel == VPSS_CCDCPG)
		temp |= 0x08;

	temp |= (src_sel << CCD_SRC_SEL_SHIFT);
	isp5_write(temp, DM365_ISP5_CCDCMUX);
}