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
struct rc_dev {struct ene_device* priv; } ;
struct ene_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  ene_rx_reset (struct ene_device*) ; 

__attribute__((used)) static void ene_set_idle(struct rc_dev *rdev, bool idle)
{
	struct ene_device *dev = rdev->priv;

	if (idle) {
		ene_rx_reset(dev);
		dbg("RX: end of data");
	}
}