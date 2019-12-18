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
struct area_priv {int flags; int /*<<< orphan*/  count; int /*<<< orphan*/  buf; int /*<<< orphan*/  addr; scalar_t__ is_write; } ;
struct anybuss_host {int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; int /*<<< orphan*/  ind_ab; int /*<<< orphan*/  power_on; } ;
struct ab_task {int /*<<< orphan*/  task_fn; scalar_t__ start_jiffies; struct area_priv area_pd; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int EIO ; 
 int ETIMEDOUT ; 
 unsigned int IND_AP_ABITS ; 
 int /*<<< orphan*/  REG_IND_AP ; 
 scalar_t__ TIMEOUT ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_bulk_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  task_fn_area_3 ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,scalar_t__) ; 
 int write_ind_ap (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int task_fn_area_2(struct anybuss_host *cd, struct ab_task *t)
{
	struct area_priv *pd = &t->area_pd;
	unsigned int ind_ap;
	int ret;

	if (!cd->power_on)
		return -EIO;
	regmap_read(cd->regmap, REG_IND_AP, &ind_ap);
	if (!(atomic_read(&cd->ind_ab) & pd->flags)) {
		/* we don't own the area yet */
		if (time_after(jiffies, t->start_jiffies + TIMEOUT)) {
			dev_warn(cd->dev, "timeout waiting for area");
			dump_stack();
			return -ETIMEDOUT;
		}
		return -EINPROGRESS;
	}
	/* we own the area, do what we're here to do */
	if (pd->is_write)
		regmap_bulk_write(cd->regmap, pd->addr, pd->buf,
				  pd->count);
	else
		regmap_bulk_read(cd->regmap, pd->addr, pd->buf,
				 pd->count);
	/* ask to release the area, must use unlocked release */
	ind_ap &= ~IND_AP_ABITS;
	ind_ap |= pd->flags;
	ret = write_ind_ap(cd->regmap, ind_ap);
	if (ret)
		return ret;
	t->task_fn = task_fn_area_3;
	return -EINPROGRESS;
}