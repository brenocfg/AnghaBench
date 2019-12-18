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
typedef  scalar_t__ u32 ;
struct paace {int /*<<< orphan*/  impl_attr; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  PAACE_IA_CID ; 
 int /*<<< orphan*/  mb () ; 
 struct paace* pamu_get_ppaace (int) ; 
 struct paace* pamu_get_spaace (struct paace*,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  set_bf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

int  pamu_update_paace_stash(int liodn, u32 subwin, u32 value)
{
	struct paace *paace;

	paace = pamu_get_ppaace(liodn);
	if (!paace) {
		pr_debug("Invalid liodn entry\n");
		return -ENOENT;
	}
	if (subwin) {
		paace = pamu_get_spaace(paace, subwin - 1);
		if (!paace)
			return -ENOENT;
	}
	set_bf(paace->impl_attr, PAACE_IA_CID, value);

	mb();

	return 0;
}