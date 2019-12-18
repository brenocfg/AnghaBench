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
struct ene_device {int rx_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  ene_rx_enable_hw (struct ene_device*) ; 

__attribute__((used)) static void ene_rx_enable(struct ene_device *dev)
{
	ene_rx_enable_hw(dev);
	dev->rx_enabled = true;
}