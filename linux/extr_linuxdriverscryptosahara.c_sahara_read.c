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
typedef  scalar_t__ u32 ;
struct sahara_dev {scalar_t__ regs_base; } ;

/* Variables and functions */
 unsigned int readl (scalar_t__) ; 

__attribute__((used)) static inline unsigned int sahara_read(struct sahara_dev *dev, u32 reg)
{
	return readl(dev->regs_base + reg);
}