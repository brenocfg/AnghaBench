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
struct solo_dev {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SOLO_MP4E_EXT_ADDR (struct solo_dev*) ; 
 unsigned int SOLO_MP4E_EXT_SIZE (struct solo_dev*) ; 
 int solo_p2m_dma_t (struct solo_dev*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int enc_get_mpeg_dma(struct solo_dev *solo_dev, dma_addr_t dma,
			      unsigned int off, unsigned int size)
{
	int ret;

	if (off > SOLO_MP4E_EXT_SIZE(solo_dev))
		return -EINVAL;

	/* Single shot */
	if (off + size <= SOLO_MP4E_EXT_SIZE(solo_dev)) {
		return solo_p2m_dma_t(solo_dev, 0, dma,
				      SOLO_MP4E_EXT_ADDR(solo_dev) + off, size,
				      0, 0);
	}

	/* Buffer wrap */
	ret = solo_p2m_dma_t(solo_dev, 0, dma,
			     SOLO_MP4E_EXT_ADDR(solo_dev) + off,
			     SOLO_MP4E_EXT_SIZE(solo_dev) - off, 0, 0);

	if (!ret) {
		ret = solo_p2m_dma_t(solo_dev, 0,
			     dma + SOLO_MP4E_EXT_SIZE(solo_dev) - off,
			     SOLO_MP4E_EXT_ADDR(solo_dev),
			     size + off - SOLO_MP4E_EXT_SIZE(solo_dev), 0, 0);
	}

	return ret;
}