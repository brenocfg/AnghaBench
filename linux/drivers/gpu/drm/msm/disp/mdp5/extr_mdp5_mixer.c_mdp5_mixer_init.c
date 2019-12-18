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
struct mdp5_lm_instance {size_t id; int /*<<< orphan*/  dspp; int /*<<< orphan*/  pp; int /*<<< orphan*/  caps; } ;
struct mdp5_hw_mixer {size_t lm; int /*<<< orphan*/  flush_mask; int /*<<< orphan*/  dspp; int /*<<< orphan*/  pp; int /*<<< orphan*/  caps; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct mdp5_hw_mixer* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct mdp5_hw_mixer* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdp_ctl_flush_mask_lm (size_t) ; 
 int /*<<< orphan*/ * mixer_names ; 

struct mdp5_hw_mixer *mdp5_mixer_init(const struct mdp5_lm_instance *lm)
{
	struct mdp5_hw_mixer *mixer;

	mixer = kzalloc(sizeof(*mixer), GFP_KERNEL);
	if (!mixer)
		return ERR_PTR(-ENOMEM);

	mixer->name = mixer_names[lm->id];
	mixer->lm = lm->id;
	mixer->caps = lm->caps;
	mixer->pp = lm->pp;
	mixer->dspp = lm->dspp;
	mixer->flush_mask = mdp_ctl_flush_mask_lm(lm->id);

	return mixer;
}