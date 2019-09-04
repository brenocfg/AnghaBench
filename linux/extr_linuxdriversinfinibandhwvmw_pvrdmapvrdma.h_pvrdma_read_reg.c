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
struct pvrdma_dev {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static inline u32 pvrdma_read_reg(struct pvrdma_dev *dev, u32 reg)
{
	return le32_to_cpu(readl(dev->regs + reg));
}