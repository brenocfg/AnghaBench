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
struct hsi_controller {struct hsi_controller* port; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct hsi_controller*) ; 
 struct hsi_controller* to_hsi_controller (struct device*) ; 

__attribute__((used)) static void hsi_controller_release(struct device *dev)
{
	struct hsi_controller *hsi = to_hsi_controller(dev);

	kfree(hsi->port);
	kfree(hsi);
}