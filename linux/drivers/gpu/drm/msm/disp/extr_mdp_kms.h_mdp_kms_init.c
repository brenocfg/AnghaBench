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
struct mdp_kms_funcs {int /*<<< orphan*/  base; } ;
struct mdp_kms {int /*<<< orphan*/  base; int /*<<< orphan*/  irq_list; struct mdp_kms_funcs const* funcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msm_kms_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void mdp_kms_init(struct mdp_kms *mdp_kms,
		const struct mdp_kms_funcs *funcs)
{
	mdp_kms->funcs = funcs;
	INIT_LIST_HEAD(&mdp_kms->irq_list);
	msm_kms_init(&mdp_kms->base, &funcs->base);
}