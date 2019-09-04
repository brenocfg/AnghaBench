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
struct r592_device {int /*<<< orphan*/  parallel_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  R592_IO ; 
 int /*<<< orphan*/  R592_IO_RESET ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  r592_set_mode (struct r592_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r592_set_reg_mask (struct r592_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void r592_host_reset(struct r592_device *dev)
{
	r592_set_reg_mask(dev, R592_IO, R592_IO_RESET);
	msleep(100);
	r592_set_mode(dev, dev->parallel_mode);
}