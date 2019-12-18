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
struct pasemi_smbus {scalar_t__ base; TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,scalar_t__,int) ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 

__attribute__((used)) static inline void reg_write(struct pasemi_smbus *smbus, int reg, int val)
{
	dev_dbg(&smbus->dev->dev, "smbus write reg %lx val %08x\n",
		smbus->base + reg, val);
	outl(val, smbus->base + reg);
}