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
typedef  int /*<<< orphan*/  uint8_t ;
struct qxl_device {int dummy; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 int wait_for_io_cmd_user (struct qxl_device*,int /*<<< orphan*/ ,long,int) ; 

__attribute__((used)) static void wait_for_io_cmd(struct qxl_device *qdev, uint8_t val, long port)
{
	int ret;

restart:
	ret = wait_for_io_cmd_user(qdev, val, port, false);
	if (ret == -ERESTARTSYS)
		goto restart;
}