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
struct paace {int /*<<< orphan*/  addr_bitfields; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  PAACE_AF_V ; 
 int /*<<< orphan*/  PAACE_V_INVALID ; 
 int /*<<< orphan*/  mb () ; 
 struct paace* pamu_get_ppaace (int) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  set_bf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int pamu_disable_liodn(int liodn)
{
	struct paace *ppaace;

	ppaace = pamu_get_ppaace(liodn);
	if (!ppaace) {
		pr_debug("Invalid primary paace entry\n");
		return -ENOENT;
	}

	set_bf(ppaace->addr_bitfields, PAACE_AF_V, PAACE_V_INVALID);
	mb();

	return 0;
}