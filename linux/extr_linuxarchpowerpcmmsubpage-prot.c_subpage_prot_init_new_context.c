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
struct subpage_prot_table {int dummy; } ;
struct TYPE_2__ {struct subpage_prot_table spt; } ;
struct mm_struct {TYPE_1__ context; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct subpage_prot_table*,int /*<<< orphan*/ ,int) ; 

void subpage_prot_init_new_context(struct mm_struct *mm)
{
	struct subpage_prot_table *spt = &mm->context.spt;

	memset(spt, 0, sizeof(*spt));
}