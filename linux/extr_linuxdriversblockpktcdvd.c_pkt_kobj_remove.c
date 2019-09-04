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
struct pktcdvd_kobj {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pkt_kobj_remove(struct pktcdvd_kobj *p)
{
	if (p)
		kobject_put(&p->kobj);
}