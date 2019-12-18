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
struct vpfe_device {int /*<<< orphan*/  ccdc; } ;
typedef  enum ccdc_frmfmt { ____Placeholder_ccdc_frmfmt } ccdc_frmfmt ;

/* Variables and functions */
 int CCDC_FRMFMT_PROGRESSIVE ; 
 int /*<<< orphan*/  VPFE_IRQ_EN_SET ; 
 unsigned int VPFE_VDINT0 ; 
 unsigned int VPFE_VDINT1 ; 
 int vpfe_ccdc_get_frame_format (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vpfe_reg_write (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void vpfe_attach_irq(struct vpfe_device *vpfe)
{
	unsigned int intr = VPFE_VDINT0;
	enum ccdc_frmfmt frame_format;

	frame_format = vpfe_ccdc_get_frame_format(&vpfe->ccdc);
	if (frame_format == CCDC_FRMFMT_PROGRESSIVE)
		intr |= VPFE_VDINT1;

	vpfe_reg_write(&vpfe->ccdc, intr, VPFE_IRQ_EN_SET);
}