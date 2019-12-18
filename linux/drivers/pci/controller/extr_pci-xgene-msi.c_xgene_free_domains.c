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
struct xgene_msi {scalar_t__ inner_domain; scalar_t__ msi_domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  irq_domain_remove (scalar_t__) ; 

__attribute__((used)) static void xgene_free_domains(struct xgene_msi *msi)
{
	if (msi->msi_domain)
		irq_domain_remove(msi->msi_domain);
	if (msi->inner_domain)
		irq_domain_remove(msi->inner_domain);
}