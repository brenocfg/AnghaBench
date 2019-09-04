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
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_DC8051_CFG_CSR_ACCESS_SEL ; 
 int DC_DC8051_CFG_CSR_ACCESS_SEL_DCC_SMASK ; 
 int DC_DC8051_CFG_CSR_ACCESS_SEL_LCB_SMASK ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void set_host_lcb_access(struct hfi1_devdata *dd)
{
	write_csr(dd, DC_DC8051_CFG_CSR_ACCESS_SEL,
		  DC_DC8051_CFG_CSR_ACCESS_SEL_DCC_SMASK |
		  DC_DC8051_CFG_CSR_ACCESS_SEL_LCB_SMASK);
}