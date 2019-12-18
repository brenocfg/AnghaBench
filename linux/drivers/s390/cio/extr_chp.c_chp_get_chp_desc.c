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
struct chp_id {int dummy; } ;
struct channel_path_desc_fmt0 {int dummy; } ;
struct channel_path {int /*<<< orphan*/  lock; int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct channel_path* chpid_to_chp (struct chp_id) ; 
 struct channel_path_desc_fmt0* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct channel_path_desc_fmt0*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

struct channel_path_desc_fmt0 *chp_get_chp_desc(struct chp_id chpid)
{
	struct channel_path *chp;
	struct channel_path_desc_fmt0 *desc;

	chp = chpid_to_chp(chpid);
	if (!chp)
		return NULL;
	desc = kmalloc(sizeof(*desc), GFP_KERNEL);
	if (!desc)
		return NULL;

	mutex_lock(&chp->lock);
	memcpy(desc, &chp->desc, sizeof(*desc));
	mutex_unlock(&chp->lock);
	return desc;
}