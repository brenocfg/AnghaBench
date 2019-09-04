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
struct protection_domain {int glx; scalar_t__ gcr3_tbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  free_gcr3_tbl_level1 (scalar_t__) ; 
 int /*<<< orphan*/  free_gcr3_tbl_level2 (scalar_t__) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 

__attribute__((used)) static void free_gcr3_table(struct protection_domain *domain)
{
	if (domain->glx == 2)
		free_gcr3_tbl_level2(domain->gcr3_tbl);
	else if (domain->glx == 1)
		free_gcr3_tbl_level1(domain->gcr3_tbl);
	else
		BUG_ON(domain->glx != 0);

	free_page((unsigned long)domain->gcr3_tbl);
}