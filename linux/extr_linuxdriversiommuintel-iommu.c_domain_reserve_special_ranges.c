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
struct dmar_domain {int /*<<< orphan*/  iovad; } ;

/* Variables and functions */
 int /*<<< orphan*/  copy_reserved_iova (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reserved_iova_list ; 

__attribute__((used)) static void domain_reserve_special_ranges(struct dmar_domain *domain)
{
	copy_reserved_iova(&reserved_iova_list, &domain->iovad);
}