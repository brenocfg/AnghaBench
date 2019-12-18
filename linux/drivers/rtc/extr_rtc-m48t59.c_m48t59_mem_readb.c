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
typedef  scalar_t__ u32 ;
struct m48t59_private {scalar_t__ ioaddr; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct m48t59_private* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  readb (scalar_t__) ; 

__attribute__((used)) static u8
m48t59_mem_readb(struct device *dev, u32 ofs)
{
	struct m48t59_private *m48t59 = dev_get_drvdata(dev);

	return readb(m48t59->ioaddr+ofs);
}