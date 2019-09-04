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
struct TYPE_2__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 TYPE_1__* parkbd_dev ; 
 int /*<<< orphan*/  parport_write_control (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void parkbd_writelines(int data)
{
	parport_write_control(parkbd_dev->port, (~data & 3) | 0x10);
}