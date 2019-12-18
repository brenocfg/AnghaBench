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
struct uwb_rc_neh {int /*<<< orphan*/  context; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;
struct uwb_rc {int /*<<< orphan*/  ctx_bm; TYPE_1__ uwb_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void __uwb_rc_ctx_put(struct uwb_rc *rc, struct uwb_rc_neh *neh)
{
	struct device *dev = &rc->uwb_dev.dev;
	if (neh->context == 0)
		return;
	if (test_bit(neh->context, rc->ctx_bm) == 0) {
		dev_err(dev, "context %u not set in bitmap\n",
			neh->context);
		WARN_ON(1);
	}
	clear_bit(neh->context, rc->ctx_bm);
	neh->context = 0;
}