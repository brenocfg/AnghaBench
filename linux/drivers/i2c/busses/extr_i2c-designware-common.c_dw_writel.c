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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct dw_i2c_dev {int flags; scalar_t__ base; } ;

/* Variables and functions */
 int ACCESS_16BIT ; 
 int ACCESS_SWAP ; 
 int swab32 (int) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 
 int /*<<< orphan*/  writew_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

void dw_writel(struct dw_i2c_dev *dev, u32 b, int offset)
{
	if (dev->flags & ACCESS_SWAP)
		b = swab32(b);

	if (dev->flags & ACCESS_16BIT) {
		writew_relaxed((u16)b, dev->base + offset);
		writew_relaxed((u16)(b >> 16), dev->base + offset + 2);
	} else {
		writel_relaxed(b, dev->base + offset);
	}
}