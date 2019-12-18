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
struct solo_p2m_desc {int dummy; } ;
struct solo_dev {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int solo_p2m_dma_desc (struct solo_dev*,struct solo_p2m_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  solo_p2m_fill_desc (struct solo_p2m_desc*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int solo_p2m_dma_t(struct solo_dev *solo_dev, int wr,
		   dma_addr_t dma_addr, u32 ext_addr, u32 size,
		   int repeat, u32 ext_size)
{
	struct solo_p2m_desc desc[2];

	solo_p2m_fill_desc(&desc[1], wr, dma_addr, ext_addr, size, repeat,
			   ext_size);

	/* No need for desc_dma since we know it is a single-shot */
	return solo_p2m_dma_desc(solo_dev, desc, 0, 1);
}