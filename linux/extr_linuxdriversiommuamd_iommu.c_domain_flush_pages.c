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
typedef  int /*<<< orphan*/  u64 ;
struct protection_domain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __domain_flush_pages (struct protection_domain*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void domain_flush_pages(struct protection_domain *domain,
			       u64 address, size_t size)
{
	__domain_flush_pages(domain, address, size, 0);
}