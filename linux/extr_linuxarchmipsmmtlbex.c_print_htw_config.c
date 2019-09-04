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

/* Variables and functions */
 unsigned int MIPS_PWCTL_DPH_MASK ; 
 unsigned int MIPS_PWCTL_DPH_SHIFT ; 
 unsigned int MIPS_PWCTL_HUGEPG_MASK ; 
 unsigned int MIPS_PWCTL_HUGEPG_SHIFT ; 
 unsigned int MIPS_PWCTL_PSN_MASK ; 
 unsigned int MIPS_PWCTL_PSN_SHIFT ; 
 unsigned int MIPS_PWCTL_PWEN_MASK ; 
 unsigned int MIPS_PWCTL_PWEN_SHIFT ; 
 unsigned int MIPS_PWCTL_XK_MASK ; 
 unsigned int MIPS_PWCTL_XK_SHIFT ; 
 unsigned int MIPS_PWCTL_XS_MASK ; 
 unsigned int MIPS_PWCTL_XS_SHIFT ; 
 unsigned int MIPS_PWCTL_XU_MASK ; 
 unsigned int MIPS_PWCTL_XU_SHIFT ; 
 unsigned long MIPS_PWFIELD_GDI_MASK ; 
 unsigned long MIPS_PWFIELD_GDI_SHIFT ; 
 unsigned long MIPS_PWFIELD_MDI_MASK ; 
 unsigned long MIPS_PWFIELD_MDI_SHIFT ; 
 unsigned long MIPS_PWFIELD_PTEI_MASK ; 
 unsigned long MIPS_PWFIELD_PTEI_SHIFT ; 
 unsigned long MIPS_PWFIELD_PTI_MASK ; 
 unsigned long MIPS_PWFIELD_PTI_SHIFT ; 
 unsigned long MIPS_PWFIELD_UDI_MASK ; 
 unsigned long MIPS_PWFIELD_UDI_SHIFT ; 
 unsigned long MIPS_PWSIZE_GDW_MASK ; 
 unsigned long MIPS_PWSIZE_GDW_SHIFT ; 
 unsigned long MIPS_PWSIZE_MDW_MASK ; 
 unsigned long MIPS_PWSIZE_MDW_SHIFT ; 
 unsigned long MIPS_PWSIZE_PS_MASK ; 
 unsigned long MIPS_PWSIZE_PS_SHIFT ; 
 unsigned long MIPS_PWSIZE_PTEW_MASK ; 
 unsigned long MIPS_PWSIZE_PTEW_SHIFT ; 
 unsigned long MIPS_PWSIZE_PTW_MASK ; 
 unsigned long MIPS_PWSIZE_PTW_SHIFT ; 
 unsigned long MIPS_PWSIZE_UDW_MASK ; 
 unsigned long MIPS_PWSIZE_UDW_SHIFT ; 
 int /*<<< orphan*/  pr_debug (char*,int const,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,...) ; 
 unsigned int read_c0_pwctl () ; 
 unsigned long read_c0_pwfield () ; 
 unsigned long read_c0_pwsize () ; 

__attribute__((used)) static void print_htw_config(void)
{
	unsigned long config;
	unsigned int pwctl;
	const int field = 2 * sizeof(unsigned long);

	config = read_c0_pwfield();
	pr_debug("PWField (0x%0*lx): GDI: 0x%02lx  UDI: 0x%02lx  MDI: 0x%02lx  PTI: 0x%02lx  PTEI: 0x%02lx\n",
		field, config,
		(config & MIPS_PWFIELD_GDI_MASK) >> MIPS_PWFIELD_GDI_SHIFT,
		(config & MIPS_PWFIELD_UDI_MASK) >> MIPS_PWFIELD_UDI_SHIFT,
		(config & MIPS_PWFIELD_MDI_MASK) >> MIPS_PWFIELD_MDI_SHIFT,
		(config & MIPS_PWFIELD_PTI_MASK) >> MIPS_PWFIELD_PTI_SHIFT,
		(config & MIPS_PWFIELD_PTEI_MASK) >> MIPS_PWFIELD_PTEI_SHIFT);

	config = read_c0_pwsize();
	pr_debug("PWSize  (0x%0*lx): PS: 0x%lx  GDW: 0x%02lx  UDW: 0x%02lx  MDW: 0x%02lx  PTW: 0x%02lx  PTEW: 0x%02lx\n",
		field, config,
		(config & MIPS_PWSIZE_PS_MASK) >> MIPS_PWSIZE_PS_SHIFT,
		(config & MIPS_PWSIZE_GDW_MASK) >> MIPS_PWSIZE_GDW_SHIFT,
		(config & MIPS_PWSIZE_UDW_MASK) >> MIPS_PWSIZE_UDW_SHIFT,
		(config & MIPS_PWSIZE_MDW_MASK) >> MIPS_PWSIZE_MDW_SHIFT,
		(config & MIPS_PWSIZE_PTW_MASK) >> MIPS_PWSIZE_PTW_SHIFT,
		(config & MIPS_PWSIZE_PTEW_MASK) >> MIPS_PWSIZE_PTEW_SHIFT);

	pwctl = read_c0_pwctl();
	pr_debug("PWCtl   (0x%x): PWEn: 0x%x  XK: 0x%x  XS: 0x%x  XU: 0x%x  DPH: 0x%x  HugePg: 0x%x  Psn: 0x%x\n",
		pwctl,
		(pwctl & MIPS_PWCTL_PWEN_MASK) >> MIPS_PWCTL_PWEN_SHIFT,
		(pwctl & MIPS_PWCTL_XK_MASK) >> MIPS_PWCTL_XK_SHIFT,
		(pwctl & MIPS_PWCTL_XS_MASK) >> MIPS_PWCTL_XS_SHIFT,
		(pwctl & MIPS_PWCTL_XU_MASK) >> MIPS_PWCTL_XU_SHIFT,
		(pwctl & MIPS_PWCTL_DPH_MASK) >> MIPS_PWCTL_DPH_SHIFT,
		(pwctl & MIPS_PWCTL_HUGEPG_MASK) >> MIPS_PWCTL_HUGEPG_SHIFT,
		(pwctl & MIPS_PWCTL_PSN_MASK) >> MIPS_PWCTL_PSN_SHIFT);
}