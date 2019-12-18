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
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,char const*,int) ; 

__attribute__((used)) static void ath10k_check_chain_mask(struct ath10k *ar, u32 cm, const char *dbg)
{
	/* It is not clear that allowing gaps in chainmask
	 * is helpful.  Probably it will not do what user
	 * is hoping for, so warn in that case.
	 */
	if (cm == 15 || cm == 7 || cm == 3 || cm == 1 || cm == 0)
		return;

	ath10k_warn(ar, "mac %s antenna chainmask may be invalid: 0x%x.  Suggested values: 15, 7, 3, 1 or 0.\n",
		    dbg, cm);
}