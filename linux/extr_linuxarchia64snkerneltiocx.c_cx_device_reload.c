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
struct TYPE_2__ {int /*<<< orphan*/  mfg_num; int /*<<< orphan*/  part_num; int /*<<< orphan*/  nasid; } ;
struct cx_dev {int /*<<< orphan*/  bt; int /*<<< orphan*/  hubdev; TYPE_1__ cx_id; } ;

/* Variables and functions */
 int cx_device_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx_device_unregister (struct cx_dev*) ; 

__attribute__((used)) static int cx_device_reload(struct cx_dev *cx_dev)
{
	cx_device_unregister(cx_dev);
	return cx_device_register(cx_dev->cx_id.nasid, cx_dev->cx_id.part_num,
				  cx_dev->cx_id.mfg_num, cx_dev->hubdev,
				  cx_dev->bt);
}