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
struct cas {int cas_flags; scalar_t__ regs; } ;

/* Variables and functions */
 int BIM_LOCAL_DEV_EXT ; 
 int BIM_LOCAL_DEV_PAD ; 
 int BIM_LOCAL_DEV_PROM ; 
 int CAS_FLAG_ENTROPY_DEV ; 
 int ENTROPY_RESET_STC_MODE ; 
 scalar_t__ REG_BIM_LOCAL_DEV_EN ; 
 scalar_t__ REG_ENTROPY_RAND_REG ; 
 scalar_t__ REG_ENTROPY_RESET ; 
 scalar_t__ readb (scalar_t__) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static inline void cas_entropy_reset(struct cas *cp)
{
#ifdef USE_ENTROPY_DEV
	if ((cp->cas_flags & CAS_FLAG_ENTROPY_DEV) == 0)
		return;

	writel(BIM_LOCAL_DEV_PAD | BIM_LOCAL_DEV_PROM | BIM_LOCAL_DEV_EXT,
	       cp->regs + REG_BIM_LOCAL_DEV_EN);
	writeb(ENTROPY_RESET_STC_MODE, cp->regs + REG_ENTROPY_RESET);
	writeb(0x55, cp->regs + REG_ENTROPY_RAND_REG);

	/* if we read back 0x0, we don't have an entropy device */
	if (readb(cp->regs + REG_ENTROPY_RAND_REG) == 0)
		cp->cas_flags &= ~CAS_FLAG_ENTROPY_DEV;
#endif
}