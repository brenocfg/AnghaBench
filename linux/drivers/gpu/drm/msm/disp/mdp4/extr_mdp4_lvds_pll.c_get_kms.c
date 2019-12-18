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
struct msm_drm_private {int /*<<< orphan*/  kms; } ;
struct mdp4_lvds_pll {TYPE_1__* dev; } ;
struct mdp4_kms {int dummy; } ;
struct TYPE_2__ {struct msm_drm_private* dev_private; } ;

/* Variables and functions */
 struct mdp4_kms* to_mdp4_kms (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_mdp_kms (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mdp4_kms *get_kms(struct mdp4_lvds_pll *lvds_pll)
{
	struct msm_drm_private *priv = lvds_pll->dev->dev_private;
	return to_mdp4_kms(to_mdp_kms(priv->kms));
}