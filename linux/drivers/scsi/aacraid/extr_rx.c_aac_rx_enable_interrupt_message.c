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
struct aac_dev {int OIMR; } ;
struct TYPE_2__ {int /*<<< orphan*/  OIMR; } ;

/* Variables and functions */
 TYPE_1__ MUnit ; 
 int /*<<< orphan*/  rx_writeb (struct aac_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void aac_rx_enable_interrupt_message(struct aac_dev *dev)
{
	rx_writeb(dev, MUnit.OIMR, dev->OIMR = 0xf7);
}