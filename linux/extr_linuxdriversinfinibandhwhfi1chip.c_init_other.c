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
 int /*<<< orphan*/  CCE_ERR_MASK ; 
 int /*<<< orphan*/  DCC_ERR_FLG_EN ; 
 int /*<<< orphan*/  DC_DC8051_ERR_EN ; 
 unsigned long long DRIVER_MISC_MASK ; 
 int /*<<< orphan*/  MISC_ERR_MASK ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,unsigned long long) ; 

__attribute__((used)) static void init_other(struct hfi1_devdata *dd)
{
	/* enable all CCE errors */
	write_csr(dd, CCE_ERR_MASK, ~0ull);
	/* enable *some* Misc errors */
	write_csr(dd, MISC_ERR_MASK, DRIVER_MISC_MASK);
	/* enable all DC errors, except LCB */
	write_csr(dd, DCC_ERR_FLG_EN, ~0ull);
	write_csr(dd, DC_DC8051_ERR_EN, ~0ull);
}