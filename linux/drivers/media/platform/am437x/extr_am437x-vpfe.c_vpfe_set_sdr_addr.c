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
struct vpfe_ccdc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VPFE_SDR_ADDR ; 
 int /*<<< orphan*/  vpfe_reg_write (struct vpfe_ccdc*,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void vpfe_set_sdr_addr(struct vpfe_ccdc *ccdc, unsigned long addr)
{
	vpfe_reg_write(ccdc, addr & 0xffffffe0, VPFE_SDR_ADDR);
}