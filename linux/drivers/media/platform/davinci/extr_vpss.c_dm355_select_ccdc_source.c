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
typedef  enum vpss_ccdc_source_sel { ____Placeholder_vpss_ccdc_source_sel } vpss_ccdc_source_sel ;

/* Variables and functions */
 int /*<<< orphan*/  DM355_VPSSBL_CCDCMUX ; 
 int VPSS_HSSISEL_SHIFT ; 
 int /*<<< orphan*/  bl_regw (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dm355_select_ccdc_source(enum vpss_ccdc_source_sel src_sel)
{
	bl_regw(src_sel << VPSS_HSSISEL_SHIFT, DM355_VPSSBL_CCDCMUX);
}