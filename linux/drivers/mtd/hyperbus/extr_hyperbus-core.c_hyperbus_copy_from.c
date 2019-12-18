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
struct map_info {int dummy; } ;
struct hyperbus_device {struct hyperbus_ctlr* ctlr; } ;
struct hyperbus_ctlr {TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* copy_from ) (struct hyperbus_device*,void*,unsigned long,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct hyperbus_device* map_to_hbdev (struct map_info*) ; 
 int /*<<< orphan*/  stub1 (struct hyperbus_device*,void*,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hyperbus_copy_from(struct map_info *map, void *to,
			       unsigned long from, ssize_t len)
{
	struct hyperbus_device *hbdev = map_to_hbdev(map);
	struct hyperbus_ctlr *ctlr = hbdev->ctlr;

	ctlr->ops->copy_from(hbdev, to, from, len);
}