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
struct dma_ops_domain {int dummy; } ;
struct device {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct protection_domain*) ; 
 int /*<<< orphan*/  __unmap_single (struct dma_ops_domain*,int /*<<< orphan*/ ,size_t,int) ; 
 struct protection_domain* get_domain (struct device*) ; 
 struct dma_ops_domain* to_dma_ops_domain (struct protection_domain*) ; 

__attribute__((used)) static void unmap_page(struct device *dev, dma_addr_t dma_addr, size_t size,
		       enum dma_data_direction dir, unsigned long attrs)
{
	struct protection_domain *domain;
	struct dma_ops_domain *dma_dom;

	domain = get_domain(dev);
	if (IS_ERR(domain))
		return;

	dma_dom = to_dma_ops_domain(domain);

	__unmap_single(dma_dom, dma_addr, size, dir);
}