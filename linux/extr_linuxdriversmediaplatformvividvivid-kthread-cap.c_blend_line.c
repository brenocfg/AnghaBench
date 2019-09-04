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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct vivid_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  copy_pix (struct vivid_dev*,unsigned int,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void blend_line(struct vivid_dev *dev, unsigned y_offset, unsigned x_offset,
		u8 *vcapbuf, const u8 *vosdbuf,
		unsigned width, unsigned pixsize)
{
	unsigned x;

	for (x = 0; x < width; x++, vcapbuf += pixsize, vosdbuf += pixsize) {
		copy_pix(dev, y_offset, x_offset + x,
			 (u16 *)vcapbuf, (const u16 *)vosdbuf);
	}
}