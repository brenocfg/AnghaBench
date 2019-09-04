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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct solo_dev {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ SOLO_MOTION_EXT_ADDR (struct solo_dev*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int const,int /*<<< orphan*/ ) ; 
 int solo_p2m_dma (struct solo_dev*,int,int /*<<< orphan*/ *,scalar_t__,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int solo_dma_vin_region(struct solo_dev *solo_dev, u32 off,
			       u16 val, int reg_size)
{
	__le16 *buf;
	const int n = 64, size = n * sizeof(*buf);
	int i, ret = 0;

	buf = kmalloc(size, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	for (i = 0; i < n; i++)
		buf[i] = cpu_to_le16(val);

	for (i = 0; i < reg_size; i += size) {
		ret = solo_p2m_dma(solo_dev, 1, buf,
				   SOLO_MOTION_EXT_ADDR(solo_dev) + off + i,
				   size, 0, 0);

		if (ret)
			break;
	}

	kfree(buf);
	return ret;
}