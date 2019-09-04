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
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  PAACE_AF_V ; 
 int /*<<< orphan*/  PAACE_V_VALID ; 
 int /*<<< orphan*/  PPAACE_AF_WSE ; 
 int /*<<< orphan*/  get_bf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 
 struct paace* pamu_get_ppaace (int) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  set_bf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int pamu_enable_liodn(int liodn)
{
	struct paace *ppaace;

	ppaace = pamu_get_ppaace(liodn);
	if (!ppaace) {
		pr_debug("Invalid primary paace entry\n");
		return -ENOENT;
	}

	if (!get_bf(ppaace->addr_bitfields, PPAACE_AF_WSE)) {
		pr_debug("liodn %d not configured\n", liodn);
		return -EINVAL;
	}

	/* Ensure that all other stores to the ppaace complete first */
	mb();

	set_bf(ppaace->addr_bitfields, PAACE_AF_V, PAACE_V_VALID);
	mb();

	return 0;
}