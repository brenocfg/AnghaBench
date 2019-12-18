#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wahc {int /*<<< orphan*/  rpipe_bm; int /*<<< orphan*/  rpipes; TYPE_1__* usb_iface; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bitmap_empty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void wa_rpipes_destroy(struct wahc *wa)
{
	struct device *dev = &wa->usb_iface->dev;

	if (!bitmap_empty(wa->rpipe_bm, wa->rpipes)) {
		WARN_ON(1);
		dev_err(dev, "BUG: pipes not released on exit: %*pb\n",
			wa->rpipes, wa->rpipe_bm);
	}
	bitmap_free(wa->rpipe_bm);
}