#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct iforce {TYPE_4__* dev; TYPE_3__* core_effects; } ;
struct TYPE_10__ {int max_effects; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; TYPE_5__* ff; } ;
struct TYPE_7__ {unsigned short start; } ;
struct TYPE_6__ {unsigned short start; } ;
struct TYPE_8__ {int /*<<< orphan*/  flags; TYPE_2__ mod2_chunk; TYPE_1__ mod1_chunk; } ;

/* Variables and functions */
 int /*<<< orphan*/  FF_CORE_IS_USED ; 
 int /*<<< orphan*/  FF_CORE_UPDATE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,unsigned short) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mark_core_as_ready(struct iforce *iforce, unsigned short addr)
{
	int i;

	if (!iforce->dev->ff)
		return 0;

	for (i = 0; i < iforce->dev->ff->max_effects; ++i) {
		if (test_bit(FF_CORE_IS_USED, iforce->core_effects[i].flags) &&
		    (iforce->core_effects[i].mod1_chunk.start == addr ||
		     iforce->core_effects[i].mod2_chunk.start == addr)) {
			clear_bit(FF_CORE_UPDATE, iforce->core_effects[i].flags);
			return 0;
		}
	}
	dev_warn(&iforce->dev->dev, "unused effect %04x updated !!!\n", addr);
	return -1;
}