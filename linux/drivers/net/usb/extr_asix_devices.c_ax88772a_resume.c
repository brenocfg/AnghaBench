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
struct usbnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ax88772_restore_phy (struct usbnet*) ; 
 int /*<<< orphan*/  ax88772a_hw_reset (struct usbnet*,int) ; 

__attribute__((used)) static void ax88772a_resume(struct usbnet *dev)
{
	int i;

	for (i = 0; i < 3; i++) {
		if (!ax88772a_hw_reset(dev, 1))
			break;
	}

	ax88772_restore_phy(dev);
}