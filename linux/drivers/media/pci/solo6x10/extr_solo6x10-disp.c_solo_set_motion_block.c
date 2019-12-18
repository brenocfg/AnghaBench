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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct solo_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ SOLO_MOTION_EXT_ADDR (struct solo_dev*) ; 
 int SOLO_MOTION_SZ ; 
 scalar_t__ SOLO_MOT_FLAG_AREA ; 
 int SOLO_MOT_THRESH_SIZE ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (unsigned int const,int /*<<< orphan*/ ) ; 
 int solo_p2m_dma (struct solo_dev*,int,int /*<<< orphan*/ *,scalar_t__,unsigned int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int solo_set_motion_block(struct solo_dev *solo_dev, u8 ch,
		const u16 *thresholds)
{
	const unsigned size = sizeof(u16) * 64;
	u32 off = SOLO_MOT_FLAG_AREA + ch * SOLO_MOT_THRESH_SIZE * 2;
	__le16 *buf;
	int x, y;
	int ret = 0;

	buf = kzalloc(size, GFP_KERNEL);
	if (buf == NULL)
		return -ENOMEM;
	for (y = 0; y < SOLO_MOTION_SZ; y++) {
		for (x = 0; x < SOLO_MOTION_SZ; x++)
			buf[x] = cpu_to_le16(thresholds[y * SOLO_MOTION_SZ + x]);
		ret |= solo_p2m_dma(solo_dev, 1, buf,
			SOLO_MOTION_EXT_ADDR(solo_dev) + off + y * size,
			size, 0, 0);
	}
	kfree(buf);
	return ret;
}