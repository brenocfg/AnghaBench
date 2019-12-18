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
struct TYPE_2__ {scalar_t__ block_size; } ;
struct tape_device {TYPE_1__ char_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_EVENT (int,char*) ; 

int
tape_std_mtreset(struct tape_device *device, int count)
{
	DBF_EVENT(6, "TCHAR:devreset:\n");
	device->char_data.block_size = 0;
	return 0;
}