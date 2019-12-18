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
struct r592_device {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  R592_STATUS ; 
 int R592_STATUS_RECV_ERR ; 
 int R592_STATUS_SEND_ERR ; 
 int r592_read_reg (struct r592_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r592_test_io_error(struct r592_device *dev)
{
	if (!(r592_read_reg(dev, R592_STATUS) &
		(R592_STATUS_SEND_ERR | R592_STATUS_RECV_ERR)))
		return 0;

	return -EIO;
}