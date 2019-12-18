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
struct bcm_iproc_i2c_dev {scalar_t__ base; int /*<<< orphan*/  idm_lock; scalar_t__ idm_base; int /*<<< orphan*/  ape_addr_mask; } ;

/* Variables and functions */
 scalar_t__ IDM_CTRL_DIRECT_OFFSET ; 
 scalar_t__ readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline u32 iproc_i2c_rd_reg(struct bcm_iproc_i2c_dev *iproc_i2c,
				   u32 offset)
{
	u32 val;

	if (iproc_i2c->idm_base) {
		spin_lock(&iproc_i2c->idm_lock);
		writel(iproc_i2c->ape_addr_mask,
		       iproc_i2c->idm_base + IDM_CTRL_DIRECT_OFFSET);
		val = readl(iproc_i2c->base + offset);
		spin_unlock(&iproc_i2c->idm_lock);
	} else {
		val = readl(iproc_i2c->base + offset);
	}

	return val;
}