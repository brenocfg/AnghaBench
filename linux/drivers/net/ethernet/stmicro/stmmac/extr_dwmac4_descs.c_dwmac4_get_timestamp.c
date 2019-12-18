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
typedef  unsigned long long u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct dma_desc {int /*<<< orphan*/  des1; int /*<<< orphan*/  des0; } ;

/* Variables and functions */
 unsigned long long le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void dwmac4_get_timestamp(void *desc, u32 ats, u64 *ts)
{
	struct dma_desc *p = (struct dma_desc *)desc;
	u64 ns;

	ns = le32_to_cpu(p->des0);
	/* convert high/sec time stamp value to nanosecond */
	ns += le32_to_cpu(p->des1) * 1000000000ULL;

	*ts = ns;
}