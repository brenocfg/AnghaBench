#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct irq_avail {scalar_t__ offset; scalar_t__ range; struct irq_avail* bitmap; } ;
struct device_node {int dummy; } ;
struct cxl {TYPE_1__* guest; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {scalar_t__ irq_base_offset; int irq_nranges; struct irq_avail* irq_avail; int /*<<< orphan*/  irq_alloc_lock; } ;

/* Variables and functions */
 int BITS_TO_LONGS (scalar_t__) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* be32_to_cpu (int /*<<< orphan*/  const) ; 
 scalar_t__ cxl_verbose ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct irq_avail*) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,int*) ; 
 int /*<<< orphan*/  pr_info (char*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int read_adapter_irq_config(struct cxl *adapter, struct device_node *np)
{
	const __be32 *ranges;
	int len, nranges, i;
	struct irq_avail *cur;

	ranges = of_get_property(np, "interrupt-ranges", &len);
	if (ranges == NULL || len < (2 * sizeof(int)))
		return -EINVAL;

	/*
	 * encoded array of two cells per entry, each cell encoded as
	 * with encode-int
	 */
	nranges = len / (2 * sizeof(int));
	if (nranges == 0 || (nranges * 2 * sizeof(int)) != len)
		return -EINVAL;

	adapter->guest->irq_avail = kcalloc(nranges, sizeof(struct irq_avail),
					    GFP_KERNEL);
	if (adapter->guest->irq_avail == NULL)
		return -ENOMEM;

	adapter->guest->irq_base_offset = be32_to_cpu(ranges[0]);
	for (i = 0; i < nranges; i++) {
		cur = &adapter->guest->irq_avail[i];
		cur->offset = be32_to_cpu(ranges[i * 2]);
		cur->range  = be32_to_cpu(ranges[i * 2 + 1]);
		cur->bitmap = kcalloc(BITS_TO_LONGS(cur->range),
				sizeof(*cur->bitmap), GFP_KERNEL);
		if (cur->bitmap == NULL)
			goto err;
		if (cur->offset < adapter->guest->irq_base_offset)
			adapter->guest->irq_base_offset = cur->offset;
		if (cxl_verbose)
			pr_info("available IRQ range: %#lx-%#lx (%lu)\n",
				cur->offset, cur->offset + cur->range - 1,
				cur->range);
	}
	adapter->guest->irq_nranges = nranges;
	spin_lock_init(&adapter->guest->irq_alloc_lock);

	return 0;
err:
	for (i--; i >= 0; i--) {
		cur = &adapter->guest->irq_avail[i];
		kfree(cur->bitmap);
	}
	kfree(adapter->guest->irq_avail);
	adapter->guest->irq_avail = NULL;
	return -ENOMEM;
}