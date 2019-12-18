#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct resource {scalar_t__ start; } ;
struct aspeed_sdhci {TYPE_2__* parent; } ;
typedef  int resource_size_t ;
struct TYPE_4__ {TYPE_1__* res; } ;
struct TYPE_3__ {scalar_t__ start; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IORESOURCE_MEM ; 
 scalar_t__ resource_type (struct resource*) ; 

__attribute__((used)) static inline int aspeed_sdhci_calculate_slot(struct aspeed_sdhci *dev,
					      struct resource *res)
{
	resource_size_t delta;

	if (!res || resource_type(res) != IORESOURCE_MEM)
		return -EINVAL;

	if (res->start < dev->parent->res->start)
		return -EINVAL;

	delta = res->start - dev->parent->res->start;
	if (delta & (0x100 - 1))
		return -EINVAL;

	return (delta / 0x100) - 1;
}