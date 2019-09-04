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
struct pt_unit {int present; int drive; int /*<<< orphan*/ * pi; int /*<<< orphan*/  name; int /*<<< orphan*/ * bufptr; scalar_t__ last_sense; scalar_t__ flags; int /*<<< orphan*/  available; int /*<<< orphan*/  pia; } ;

/* Variables and functions */
 int* DU ; 
 size_t D_DLY ; 
 size_t D_MOD ; 
 size_t D_PRO ; 
 size_t D_PRT ; 
 size_t D_SLV ; 
 size_t D_UNI ; 
 int /*<<< orphan*/  PI_PT ; 
 int /*<<< orphan*/  PT_NAMELEN ; 
 int PT_UNITS ; 
 int /*<<< orphan*/  PT_VERSION ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  major ; 
 char* name ; 
 int /*<<< orphan*/  par_drv ; 
 scalar_t__ pi_init (int /*<<< orphan*/ *,int,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pi_register_driver (char*) ; 
 int /*<<< orphan*/  pi_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pi_unregister_driver (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,char*) ; 
 int /*<<< orphan*/  printk (char*,char*,...) ; 
 struct pt_unit* pt ; 
 int /*<<< orphan*/  pt_probe (struct pt_unit*) ; 
 int /*<<< orphan*/  pt_scratch ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  verbose ; 

__attribute__((used)) static int pt_detect(void)
{
	struct pt_unit *tape;
	int specified = 0, found = 0;
	int unit;

	printk("%s: %s version %s, major %d\n", name, name, PT_VERSION, major);

	par_drv = pi_register_driver(name);
	if (!par_drv) {
		pr_err("failed to register %s driver\n", name);
		return -1;
	}

	specified = 0;
	for (unit = 0; unit < PT_UNITS; unit++) {
		struct pt_unit *tape = &pt[unit];
		tape->pi = &tape->pia;
		atomic_set(&tape->available, 1);
		tape->flags = 0;
		tape->last_sense = 0;
		tape->present = 0;
		tape->bufptr = NULL;
		tape->drive = DU[D_SLV];
		snprintf(tape->name, PT_NAMELEN, "%s%d", name, unit);
		if (!DU[D_PRT])
			continue;
		specified++;
		if (pi_init(tape->pi, 0, DU[D_PRT], DU[D_MOD], DU[D_UNI],
		     DU[D_PRO], DU[D_DLY], pt_scratch, PI_PT,
		     verbose, tape->name)) {
			if (!pt_probe(tape)) {
				tape->present = 1;
				found++;
			} else
				pi_release(tape->pi);
		}
	}
	if (specified == 0) {
		tape = pt;
		if (pi_init(tape->pi, 1, -1, -1, -1, -1, -1, pt_scratch,
			    PI_PT, verbose, tape->name)) {
			if (!pt_probe(tape)) {
				tape->present = 1;
				found++;
			} else
				pi_release(tape->pi);
		}

	}
	if (found)
		return 0;

	pi_unregister_driver(par_drv);
	printk("%s: No ATAPI tape drive detected\n", name);
	return -1;
}