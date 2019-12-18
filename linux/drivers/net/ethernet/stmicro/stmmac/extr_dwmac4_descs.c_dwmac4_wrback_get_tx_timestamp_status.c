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
struct dma_desc {int /*<<< orphan*/  des3; } ;

/* Variables and functions */
 int TDES3_CONTEXT_TYPE ; 
 int TDES3_TIMESTAMP_STATUS ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dwmac4_wrback_get_tx_timestamp_status(struct dma_desc *p)
{
	/* Context type from W/B descriptor must be zero */
	if (le32_to_cpu(p->des3) & TDES3_CONTEXT_TYPE)
		return 0;

	/* Tx Timestamp Status is 1 so des0 and des1'll have valid values */
	if (le32_to_cpu(p->des3) & TDES3_TIMESTAMP_STATUS)
		return 1;

	return 0;
}