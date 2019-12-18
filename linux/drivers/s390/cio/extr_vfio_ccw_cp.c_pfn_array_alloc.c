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
typedef  unsigned int u64 ;
struct pfn_array {unsigned int pa_nr; unsigned int* pa_iova_pfn; unsigned int pa_iova; unsigned int* pa_pfn; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int PAGE_MASK ; 
 unsigned int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 unsigned int* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int pfn_array_alloc(struct pfn_array *pa, u64 iova, unsigned int len)
{
	int i;

	if (pa->pa_nr || pa->pa_iova_pfn)
		return -EINVAL;

	pa->pa_iova = iova;

	pa->pa_nr = ((iova & ~PAGE_MASK) + len + (PAGE_SIZE - 1)) >> PAGE_SHIFT;
	if (!pa->pa_nr)
		return -EINVAL;

	pa->pa_iova_pfn = kcalloc(pa->pa_nr,
				  sizeof(*pa->pa_iova_pfn) +
				  sizeof(*pa->pa_pfn),
				  GFP_KERNEL);
	if (unlikely(!pa->pa_iova_pfn)) {
		pa->pa_nr = 0;
		return -ENOMEM;
	}
	pa->pa_pfn = pa->pa_iova_pfn + pa->pa_nr;

	pa->pa_iova_pfn[0] = pa->pa_iova >> PAGE_SHIFT;
	pa->pa_pfn[0] = -1ULL;
	for (i = 1; i < pa->pa_nr; i++) {
		pa->pa_iova_pfn[i] = pa->pa_iova_pfn[i - 1] + 1;
		pa->pa_pfn[i] = -1ULL;
	}

	return 0;
}