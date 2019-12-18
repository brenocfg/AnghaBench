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
struct gasket_dev {int dummy; } ;

/* Variables and functions */
 int GASKET_STATUS_ALIVE ; 

__attribute__((used)) static int apex_get_status(struct gasket_dev *gasket_dev)
{
	/* TODO: Check device status. */
	return GASKET_STATUS_ALIVE;
}