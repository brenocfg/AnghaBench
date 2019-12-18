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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct ssbi {int (* write ) (struct ssbi*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ;int /*<<< orphan*/  lock; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct ssbi* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct ssbi*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

int ssbi_write(struct device *dev, u16 addr, const u8 *buf, int len)
{
	struct ssbi *ssbi = dev_get_drvdata(dev);
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&ssbi->lock, flags);
	ret = ssbi->write(ssbi, addr, buf, len);
	spin_unlock_irqrestore(&ssbi->lock, flags);

	return ret;
}