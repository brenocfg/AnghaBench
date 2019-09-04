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
struct coresight_device {int enable; int /*<<< orphan*/  refcnt; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* disable ) (struct coresight_device*) ;} ;

/* Variables and functions */
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ ) ; 
 TYPE_1__* sink_ops (struct coresight_device*) ; 
 int /*<<< orphan*/  stub1 (struct coresight_device*) ; 

__attribute__((used)) static void coresight_disable_sink(struct coresight_device *csdev)
{
	if (atomic_dec_return(csdev->refcnt) == 0) {
		if (sink_ops(csdev)->disable) {
			sink_ops(csdev)->disable(csdev);
			csdev->enable = false;
		}
	}
}