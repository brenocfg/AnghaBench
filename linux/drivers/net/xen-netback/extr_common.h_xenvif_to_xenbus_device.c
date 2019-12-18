#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xenvif {TYPE_2__* dev; } ;
struct xenbus_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 struct xenbus_device* to_xenbus_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct xenbus_device *xenvif_to_xenbus_device(struct xenvif *vif)
{
	return to_xenbus_device(vif->dev->dev.parent);
}