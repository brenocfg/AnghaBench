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
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct typec_altmode {char* desc; int /*<<< orphan*/ * ops; TYPE_1__ dev; int /*<<< orphan*/  vdo; } ;
struct dp_altmode {int /*<<< orphan*/  work; int /*<<< orphan*/  state; struct typec_altmode* alt; struct typec_altmode const* port; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int DP_CAP_DFP_D_PIN_ASSIGN (int /*<<< orphan*/ ) ; 
 int DP_CAP_UFP_D_PIN_ASSIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_STATE_ENTER ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct dp_altmode* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dp_altmode_group ; 
 int /*<<< orphan*/  dp_altmode_ops ; 
 int /*<<< orphan*/  dp_altmode_work ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct typec_altmode* typec_altmode_get_partner (struct typec_altmode*) ; 
 int /*<<< orphan*/  typec_altmode_set_drvdata (struct typec_altmode*,struct dp_altmode*) ; 

int dp_altmode_probe(struct typec_altmode *alt)
{
	const struct typec_altmode *port = typec_altmode_get_partner(alt);
	struct dp_altmode *dp;
	int ret;

	/* FIXME: Port can only be DFP_U. */

	/* Make sure we have compatiple pin configurations */
	if (!(DP_CAP_DFP_D_PIN_ASSIGN(port->vdo) &
	      DP_CAP_UFP_D_PIN_ASSIGN(alt->vdo)) &&
	    !(DP_CAP_UFP_D_PIN_ASSIGN(port->vdo) &
	      DP_CAP_DFP_D_PIN_ASSIGN(alt->vdo)))
		return -ENODEV;

	ret = sysfs_create_group(&alt->dev.kobj, &dp_altmode_group);
	if (ret)
		return ret;

	dp = devm_kzalloc(&alt->dev, sizeof(*dp), GFP_KERNEL);
	if (!dp)
		return -ENOMEM;

	INIT_WORK(&dp->work, dp_altmode_work);
	mutex_init(&dp->lock);
	dp->port = port;
	dp->alt = alt;

	alt->desc = "DisplayPort";
	alt->ops = &dp_altmode_ops;

	typec_altmode_set_drvdata(alt, dp);

	dp->state = DP_STATE_ENTER;
	schedule_work(&dp->work);

	return 0;
}