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
struct reset_controller_dev {int dummy; } ;
struct hsdk_rst {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  hsdk_reset_config (struct hsdk_rst*,unsigned long) ; 
 int hsdk_reset_do (struct hsdk_rst*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct hsdk_rst* to_hsdk_rst (struct reset_controller_dev*) ; 

__attribute__((used)) static int hsdk_reset_reset(struct reset_controller_dev *rcdev,
			      unsigned long id)
{
	struct hsdk_rst *rst = to_hsdk_rst(rcdev);
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&rst->lock, flags);
	hsdk_reset_config(rst, id);
	ret = hsdk_reset_do(rst);
	spin_unlock_irqrestore(&rst->lock, flags);

	return ret;
}