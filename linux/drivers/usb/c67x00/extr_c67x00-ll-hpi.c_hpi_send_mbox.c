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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct c67x00_device {TYPE_1__ hpi; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPI_MAILBOX ; 
 int /*<<< orphan*/  hpi_write_reg (struct c67x00_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static u16 hpi_send_mbox(struct c67x00_device *dev, u16 value)
{
	unsigned long flags;

	spin_lock_irqsave(&dev->hpi.lock, flags);
	hpi_write_reg(dev, HPI_MAILBOX, value);
	spin_unlock_irqrestore(&dev->hpi.lock, flags);

	return value;
}