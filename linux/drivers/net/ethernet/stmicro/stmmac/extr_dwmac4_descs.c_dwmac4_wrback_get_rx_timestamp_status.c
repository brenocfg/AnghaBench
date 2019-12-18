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
typedef  int /*<<< orphan*/  u32 ;
struct dma_desc {int /*<<< orphan*/  des1; int /*<<< orphan*/  des3; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int RDES1_TIMESTAMP_AVAILABLE ; 
 int RDES3_RDES1_VALID ; 
 int dwmac4_rx_check_timestamp (void*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static int dwmac4_wrback_get_rx_timestamp_status(void *desc, void *next_desc,
						 u32 ats)
{
	struct dma_desc *p = (struct dma_desc *)desc;
	int ret = -EINVAL;

	/* Get the status from normal w/b descriptor */
	if (likely(le32_to_cpu(p->des3) & RDES3_RDES1_VALID)) {
		if (likely(le32_to_cpu(p->des1) & RDES1_TIMESTAMP_AVAILABLE)) {
			int i = 0;

			/* Check if timestamp is OK from context descriptor */
			do {
				ret = dwmac4_rx_check_timestamp(next_desc);
				if (ret < 0)
					goto exit;
				i++;

			} while ((ret == 1) && (i < 10));

			if (i == 10)
				ret = -EBUSY;
		}
	}
exit:
	if (likely(ret == 0))
		return 1;

	return 0;
}