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
struct pdata_init {int /*<<< orphan*/  (* fn ) () ;scalar_t__ compatible; } ;

/* Variables and functions */
 scalar_t__ of_machine_is_compatible (scalar_t__) ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void pdata_quirks_check(struct pdata_init *quirks)
{
	while (quirks->compatible) {
		if (of_machine_is_compatible(quirks->compatible)) {
			if (quirks->fn)
				quirks->fn();
		}
		quirks++;
	}
}