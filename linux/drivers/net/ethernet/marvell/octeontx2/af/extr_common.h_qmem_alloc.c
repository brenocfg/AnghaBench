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
struct qmem {int entry_sz; int qsize; scalar_t__ align; scalar_t__ iova; scalar_t__ base; scalar_t__ alloc_sz; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ALIGN (int /*<<< orphan*/ ,scalar_t__) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ OTX2_ALIGN ; 
 struct qmem* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_alloc_coherent (struct device*,scalar_t__,scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int qmem_alloc(struct device *dev, struct qmem **q,
			     int qsize, int entry_sz)
{
	struct qmem *qmem;
	int aligned_addr;

	if (!qsize)
		return -EINVAL;

	*q = devm_kzalloc(dev, sizeof(*qmem), GFP_KERNEL);
	if (!*q)
		return -ENOMEM;
	qmem = *q;

	qmem->entry_sz = entry_sz;
	qmem->alloc_sz = (qsize * entry_sz) + OTX2_ALIGN;
	qmem->base = dma_alloc_coherent(dev, qmem->alloc_sz,
					 &qmem->iova, GFP_KERNEL);
	if (!qmem->base)
		return -ENOMEM;

	qmem->qsize = qsize;

	aligned_addr = ALIGN((u64)qmem->iova, OTX2_ALIGN);
	qmem->align = (aligned_addr - qmem->iova);
	qmem->base += qmem->align;
	qmem->iova += qmem->align;
	return 0;
}