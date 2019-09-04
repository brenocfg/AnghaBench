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
typedef  size_t u32 ;
struct paace {size_t fspi; int /*<<< orphan*/  impl_attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAACE_IA_WCE ; 
 int get_bf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 struct paace* spaact ; 

__attribute__((used)) static struct paace *pamu_get_spaace(struct paace *paace, u32 wnum)
{
	u32 subwin_cnt;
	struct paace *spaace = NULL;

	subwin_cnt = 1UL << (get_bf(paace->impl_attr, PAACE_IA_WCE) + 1);

	if (wnum < subwin_cnt)
		spaace = &spaact[paace->fspi + wnum];
	else
		pr_debug("secondary paace out of bounds\n");

	return spaace;
}