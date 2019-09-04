#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct neponset_drvdata {TYPE_1__** gpio; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_multiple ) (TYPE_1__*,unsigned long*,unsigned long*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*) ; 
 struct neponset_drvdata* nep ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,unsigned long*,unsigned long*) ; 

void neponset_ncr_frob(unsigned int mask, unsigned int val)
{
	struct neponset_drvdata *n = nep;
	unsigned long m = mask, v = val;

	if (nep)
		n->gpio[0]->set_multiple(n->gpio[0], &m, &v);
	else
		WARN(1, "nep unset\n");
}