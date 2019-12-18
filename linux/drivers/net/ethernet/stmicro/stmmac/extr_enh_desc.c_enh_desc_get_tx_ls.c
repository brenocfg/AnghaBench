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
struct dma_desc {int /*<<< orphan*/  des0; } ;

/* Variables and functions */
 int ETDES0_LAST_SEGMENT ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int enh_desc_get_tx_ls(struct dma_desc *p)
{
	return (le32_to_cpu(p->des0) & ETDES0_LAST_SEGMENT) >> 29;
}