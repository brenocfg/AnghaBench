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
struct enetc_cbdr {int bd_count; int /*<<< orphan*/ * bd_base; int /*<<< orphan*/  bd_dma_base; } ;
struct enetc_cbd {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enetc_free_cbdr(struct device *dev, struct enetc_cbdr *cbdr)
{
	int size = cbdr->bd_count * sizeof(struct enetc_cbd);

	dma_free_coherent(dev, size, cbdr->bd_base, cbdr->bd_dma_base);
	cbdr->bd_base = NULL;
}