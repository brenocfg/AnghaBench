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
struct he_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CON_CTL ; 
 unsigned int CON_CTL_ADDR (unsigned int) ; 
 int CON_CTL_BUSY ; 
 unsigned int CON_CTL_READ ; 
 int /*<<< orphan*/  CON_DAT ; 
 int he_readl (struct he_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  he_writel (struct he_dev*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned
he_readl_internal(struct he_dev *he_dev, unsigned addr, unsigned flags)
{
	he_writel(he_dev, flags | CON_CTL_READ | CON_CTL_ADDR(addr), CON_CTL);
	while (he_readl(he_dev, CON_CTL) & CON_CTL_BUSY);
	return he_readl(he_dev, CON_DAT);
}