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
struct b53_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B53_CTRL_PAGE ; 
 int /*<<< orphan*/  B53_FAST_AGE_CTRL ; 
 int ETIMEDOUT ; 
 int FAST_AGE_DONE ; 
 int FAST_AGE_DYNAMIC ; 
 int /*<<< orphan*/  b53_read8 (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  b53_write8 (struct b53_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int b53_flush_arl(struct b53_device *dev, u8 mask)
{
	unsigned int i;

	b53_write8(dev, B53_CTRL_PAGE, B53_FAST_AGE_CTRL,
		   FAST_AGE_DONE | FAST_AGE_DYNAMIC | mask);

	for (i = 0; i < 10; i++) {
		u8 fast_age_ctrl;

		b53_read8(dev, B53_CTRL_PAGE, B53_FAST_AGE_CTRL,
			  &fast_age_ctrl);

		if (!(fast_age_ctrl & FAST_AGE_DONE))
			goto out;

		msleep(1);
	}

	return -ETIMEDOUT;
out:
	/* Only age dynamic entries (default behavior) */
	b53_write8(dev, B53_CTRL_PAGE, B53_FAST_AGE_CTRL, FAST_AGE_DYNAMIC);
	return 0;
}