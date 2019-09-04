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
struct blkfront_info {int feature_discard; unsigned int discard_granularity; unsigned int discard_alignment; int feature_secdiscard; TYPE_1__* xbdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  otherend; } ;

/* Variables and functions */
 int /*<<< orphan*/  XBT_NIL ; 
 int xenbus_gather (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,unsigned int*,char*,char*,unsigned int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xenbus_read_unsigned (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void blkfront_setup_discard(struct blkfront_info *info)
{
	int err;
	unsigned int discard_granularity;
	unsigned int discard_alignment;

	info->feature_discard = 1;
	err = xenbus_gather(XBT_NIL, info->xbdev->otherend,
		"discard-granularity", "%u", &discard_granularity,
		"discard-alignment", "%u", &discard_alignment,
		NULL);
	if (!err) {
		info->discard_granularity = discard_granularity;
		info->discard_alignment = discard_alignment;
	}
	info->feature_secdiscard =
		!!xenbus_read_unsigned(info->xbdev->otherend, "discard-secure",
				       0);
}