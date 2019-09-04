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
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static pmd_t *resume_one_md_table_init(pgd_t *pgd)
{
	pud_t *pud;
	pmd_t *pmd_table;

	pud = pud_offset(pgd, 0);
	pmd_table = pmd_offset(pud, 0);

	return pmd_table;
}