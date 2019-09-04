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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  TLCLK_REG2 ; 
 int /*<<< orphan*/  event_lock ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned long) ; 

__attribute__((used)) static ssize_t show_alarms(struct device *d,
		struct device_attribute *attr,  char *buf)
{
	unsigned long ret_val;
	unsigned long flags;

	spin_lock_irqsave(&event_lock, flags);
	ret_val = (inb(TLCLK_REG2) & 0xf0);
	spin_unlock_irqrestore(&event_lock, flags);

	return sprintf(buf, "0x%lX\n", ret_val);
}