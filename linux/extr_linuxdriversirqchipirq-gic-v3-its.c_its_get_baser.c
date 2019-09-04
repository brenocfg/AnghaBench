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
struct its_node {struct its_baser* tables; } ;
struct its_baser {int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int GITS_BASER_NR_REGS ; 
 scalar_t__ GITS_BASER_TYPE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct its_baser *its_get_baser(struct its_node *its, u32 type)
{
	int i;

	for (i = 0; i < GITS_BASER_NR_REGS; i++) {
		if (GITS_BASER_TYPE(its->tables[i].val) == type)
			return &its->tables[i];
	}

	return NULL;
}