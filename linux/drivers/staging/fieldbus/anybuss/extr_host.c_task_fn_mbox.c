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
struct mbox_priv {int msg_out_sz; int /*<<< orphan*/ * msg; int /*<<< orphan*/  hdr; } ;
struct anybuss_host {int /*<<< orphan*/  regmap; int /*<<< orphan*/  ind_ab; int /*<<< orphan*/  power_on; } ;
struct ab_task {int /*<<< orphan*/  task_fn; scalar_t__ start_jiffies; struct mbox_priv mbox_pd; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int EIO ; 
 int ETIMEDOUT ; 
 unsigned int IND_AX_MIN ; 
 scalar_t__ MBOX_IN_AREA ; 
 int /*<<< orphan*/  REG_IND_AP ; 
 scalar_t__ TIMEOUT ; 
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  regmap_bulk_write (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  task_fn_mbox_2 ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 int write_ind_ap (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int task_fn_mbox(struct anybuss_host *cd, struct ab_task *t)
{
	struct mbox_priv *pd = &t->mbox_pd;
	unsigned int ind_ap;
	int ret;

	if (!cd->power_on)
		return -EIO;
	regmap_read(cd->regmap, REG_IND_AP, &ind_ap);
	if ((atomic_read(&cd->ind_ab) ^ ind_ap) & IND_AX_MIN) {
		/* mbox input area busy */
		if (time_after(jiffies, t->start_jiffies + TIMEOUT))
			return -ETIMEDOUT;
		return -EINPROGRESS;
	}
	/* write the header and msg to input area */
	regmap_bulk_write(cd->regmap, MBOX_IN_AREA, &pd->hdr,
			  sizeof(pd->hdr));
	regmap_bulk_write(cd->regmap, MBOX_IN_AREA + sizeof(pd->hdr),
			  pd->msg, pd->msg_out_sz);
	/* tell anybus we gave it a message */
	ind_ap ^= IND_AX_MIN;
	ret = write_ind_ap(cd->regmap, ind_ap);
	if (ret)
		return ret;
	t->start_jiffies = jiffies;
	t->task_fn = task_fn_mbox_2;
	return -EINPROGRESS;
}