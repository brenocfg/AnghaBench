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
struct nlm_soc_info {int coremask; int ebase; int /*<<< orphan*/  piclock; scalar_t__ socbus; int /*<<< orphan*/  picbase; int /*<<< orphan*/  sysbase; } ;

/* Variables and functions */
 int MIPS_EBASE_BASE ; 
 scalar_t__ cpu_is_xlp9xx () ; 
 struct nlm_soc_info* nlm_get_node (int) ; 
 int /*<<< orphan*/  nlm_get_pic_regbase (int) ; 
 int /*<<< orphan*/  nlm_get_sys_regbase (int) ; 
 int read_c0_ebase () ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ xlp9xx_get_socbus (int) ; 

void nlm_node_init(int node)
{
	struct nlm_soc_info *nodep;

	nodep = nlm_get_node(node);
	if (node == 0)
		nodep->coremask = 1;	/* node 0, boot cpu */
	nodep->sysbase = nlm_get_sys_regbase(node);
	nodep->picbase = nlm_get_pic_regbase(node);
	nodep->ebase = read_c0_ebase() & MIPS_EBASE_BASE;
	if (cpu_is_xlp9xx())
		nodep->socbus = xlp9xx_get_socbus(node);
	else
		nodep->socbus = 0;
	spin_lock_init(&nodep->piclock);
}