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
struct area_priv {unsigned int flags; } ;
struct anybuss_host {int /*<<< orphan*/  regmap; int /*<<< orphan*/  power_on; } ;
struct ab_task {int /*<<< orphan*/  task_fn; struct area_priv area_pd; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int EIO ; 
 unsigned int IND_AP_ABITS ; 
 unsigned int IND_AP_ACTION ; 
 unsigned int IND_AP_LOCK ; 
 int /*<<< orphan*/  REG_IND_AP ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  task_fn_area_2 ; 
 int write_ind_ap (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int task_fn_area(struct anybuss_host *cd, struct ab_task *t)
{
	struct area_priv *pd = &t->area_pd;
	unsigned int ind_ap;
	int ret;

	if (!cd->power_on)
		return -EIO;
	regmap_read(cd->regmap, REG_IND_AP, &ind_ap);
	/* ask to take the area */
	ind_ap &= ~IND_AP_ABITS;
	ind_ap |= pd->flags | IND_AP_ACTION | IND_AP_LOCK;
	ret = write_ind_ap(cd->regmap, ind_ap);
	if (ret)
		return ret;
	t->task_fn = task_fn_area_2;
	return -EINPROGRESS;
}