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
struct paace {size_t fspi; int /*<<< orphan*/  addr_bitfields; int /*<<< orphan*/  impl_attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAACE_IA_WCE ; 
 int /*<<< orphan*/  PPAACE_AF_MW ; 
 int /*<<< orphan*/  gen_pool_free (int /*<<< orphan*/ ,unsigned long,int) ; 
 int get_bf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct paace* pamu_get_ppaace (int) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  set_bf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spaace_pool ; 
 int /*<<< orphan*/ * spaact ; 

void pamu_free_subwins(int liodn)
{
	struct paace *ppaace;
	u32 subwin_cnt, size;

	ppaace = pamu_get_ppaace(liodn);
	if (!ppaace) {
		pr_debug("Invalid liodn entry\n");
		return;
	}

	if (get_bf(ppaace->addr_bitfields, PPAACE_AF_MW)) {
		subwin_cnt = 1UL << (get_bf(ppaace->impl_attr, PAACE_IA_WCE) + 1);
		size = (subwin_cnt - 1) * sizeof(struct paace);
		gen_pool_free(spaace_pool, (unsigned long)&spaact[ppaace->fspi], size);
		set_bf(ppaace->addr_bitfields, PPAACE_AF_MW, 0);
	}
}