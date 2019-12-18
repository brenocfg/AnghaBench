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
 int /*<<< orphan*/  VPFE_SYNMODE ; 
 int vpfe_reg_read (struct vpfe_ccdc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int vpfe_ccdc_getfid(struct vpfe_ccdc *ccdc)
{
	return (vpfe_reg_read(ccdc, VPFE_SYNMODE) >> 15) & 1;
}