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
struct nuc900_nand {int /*<<< orphan*/  lock; scalar_t__ reg; } ;

/* Variables and functions */
 unsigned int READYBUSY ; 
 scalar_t__ REG_SMISR ; 
 unsigned int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nuc900_check_rb(struct nuc900_nand *nand)
{
	unsigned int val;
	spin_lock(&nand->lock);
	val = __raw_readl(nand->reg + REG_SMISR);
	val &= READYBUSY;
	spin_unlock(&nand->lock);

	return val;
}