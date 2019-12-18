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
typedef  int /*<<< orphan*/  u32 ;
struct smsc911x_data {int /*<<< orphan*/  dev_lock; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* reg_write ) (struct smsc911x_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct smsc911x_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void smsc911x_reg_write(struct smsc911x_data *pdata, u32 reg,
				      u32 val)
{
	unsigned long flags;

	spin_lock_irqsave(&pdata->dev_lock, flags);
	pdata->ops->reg_write(pdata, reg, val);
	spin_unlock_irqrestore(&pdata->dev_lock, flags);
}