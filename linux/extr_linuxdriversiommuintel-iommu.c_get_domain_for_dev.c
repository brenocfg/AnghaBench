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
struct dmar_domain {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  domain_exit (struct dmar_domain*) ; 
 struct dmar_domain* find_domain (struct device*) ; 
 struct dmar_domain* find_or_alloc_domain (struct device*,int) ; 
 struct dmar_domain* set_domain_for_dev (struct device*,struct dmar_domain*) ; 

__attribute__((used)) static struct dmar_domain *get_domain_for_dev(struct device *dev, int gaw)
{
	struct dmar_domain *domain, *tmp;

	domain = find_domain(dev);
	if (domain)
		goto out;

	domain = find_or_alloc_domain(dev, gaw);
	if (!domain)
		goto out;

	tmp = set_domain_for_dev(dev, domain);
	if (!tmp || domain != tmp) {
		domain_exit(domain);
		domain = tmp;
	}

out:

	return domain;
}