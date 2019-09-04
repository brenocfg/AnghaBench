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
struct ab8500 {int (* write ) (struct ab8500*,int,int) ;int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct ab8500*,int,int) ; 

__attribute__((used)) static int set_register_interruptible(struct ab8500 *ab8500, u8 bank,
	u8 reg, u8 data)
{
	int ret;
	/*
	 * Put the u8 bank and u8 register together into a an u16.
	 * The bank on higher 8 bits and register in lower 8 bits.
	 */
	u16 addr = ((u16)bank) << 8 | reg;

	dev_vdbg(ab8500->dev, "wr: addr %#x <= %#x\n", addr, data);

	mutex_lock(&ab8500->lock);

	ret = ab8500->write(ab8500, addr, data);
	if (ret < 0)
		dev_err(ab8500->dev, "failed to write reg %#x: %d\n",
			addr, ret);
	mutex_unlock(&ab8500->lock);

	return ret;
}