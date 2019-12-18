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
typedef  int u8 ;
typedef  int u16 ;
struct ab8500 {int (* read ) (struct ab8500*,int) ;int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct ab8500*,int) ; 

__attribute__((used)) static int get_register_interruptible(struct ab8500 *ab8500, u8 bank,
	u8 reg, u8 *value)
{
	int ret;
	u16 addr = ((u16)bank) << 8 | reg;

	mutex_lock(&ab8500->lock);

	ret = ab8500->read(ab8500, addr);
	if (ret < 0)
		dev_err(ab8500->dev, "failed to read reg %#x: %d\n",
			addr, ret);
	else
		*value = ret;

	mutex_unlock(&ab8500->lock);
	dev_vdbg(ab8500->dev, "rd: addr %#x => data %#x\n", addr, ret);

	return (ret < 0) ? ret : 0;
}