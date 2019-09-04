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
struct TYPE_2__ {int /*<<< orphan*/ * pte; int /*<<< orphan*/ * pmd; int /*<<< orphan*/ * pud; int /*<<< orphan*/ * p4d; } ;
struct kimage {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_page (unsigned long) ; 

__attribute__((used)) static void free_transition_pgtable(struct kimage *image)
{
	free_page((unsigned long)image->arch.p4d);
	image->arch.p4d = NULL;
	free_page((unsigned long)image->arch.pud);
	image->arch.pud = NULL;
	free_page((unsigned long)image->arch.pmd);
	image->arch.pmd = NULL;
	free_page((unsigned long)image->arch.pte);
	image->arch.pte = NULL;
}