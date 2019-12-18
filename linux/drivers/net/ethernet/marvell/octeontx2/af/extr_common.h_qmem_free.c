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
struct qmem {scalar_t__ align; scalar_t__ iova; scalar_t__ base; int /*<<< orphan*/  alloc_sz; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_kfree (struct device*,struct qmem*) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void qmem_free(struct device *dev, struct qmem *qmem)
{
	if (!qmem)
		return;

	if (qmem->base)
		dma_free_coherent(dev, qmem->alloc_sz,
				  qmem->base - qmem->align,
				  qmem->iova - qmem->align);
	devm_kfree(dev, qmem);
}