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
struct protection_domain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  domain_flush_devices (struct protection_domain*) ; 
 int /*<<< orphan*/  domain_flush_tlb_pde (struct protection_domain*) ; 
 int /*<<< orphan*/  update_device_table (struct protection_domain*) ; 

__attribute__((used)) static void update_domain(struct protection_domain *domain)
{
	update_device_table(domain);

	domain_flush_devices(domain);
	domain_flush_tlb_pde(domain);
}