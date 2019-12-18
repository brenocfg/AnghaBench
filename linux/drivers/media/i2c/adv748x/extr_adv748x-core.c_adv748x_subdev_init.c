#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_subdev_ops {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/ * ops; int /*<<< orphan*/  function; } ;
struct v4l2_subdev {TYPE_4__ entity; int /*<<< orphan*/  name; TYPE_2__* dev; int /*<<< orphan*/  owner; int /*<<< orphan*/  flags; } ;
struct adv748x_state {TYPE_3__* client; TYPE_2__* dev; } ;
struct TYPE_7__ {int addr; int /*<<< orphan*/  adapter; } ;
struct TYPE_6__ {TYPE_1__* driver; } ;
struct TYPE_5__ {char* name; int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_SUBDEV_FL_HAS_DEVNODE ; 
 int /*<<< orphan*/  adv748x_media_ops ; 
 int /*<<< orphan*/  adv748x_sd_to_csi2 (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  adv748x_tx_media_ops ; 
 int i2c_adapter_id (int /*<<< orphan*/ ) ; 
 scalar_t__ is_tx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int,int,char const*) ; 
 int /*<<< orphan*/  v4l2_set_subdevdata (struct v4l2_subdev*,struct adv748x_state*) ; 
 int /*<<< orphan*/  v4l2_subdev_init (struct v4l2_subdev*,struct v4l2_subdev_ops const*) ; 

void adv748x_subdev_init(struct v4l2_subdev *sd, struct adv748x_state *state,
			 const struct v4l2_subdev_ops *ops, u32 function,
			 const char *ident)
{
	v4l2_subdev_init(sd, ops);
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;

	/* the owner is the same as the i2c_client's driver owner */
	sd->owner = state->dev->driver->owner;
	sd->dev = state->dev;

	v4l2_set_subdevdata(sd, state);

	/* initialize name */
	snprintf(sd->name, sizeof(sd->name), "%s %d-%04x %s",
		state->dev->driver->name,
		i2c_adapter_id(state->client->adapter),
		state->client->addr, ident);

	sd->entity.function = function;
	sd->entity.ops = is_tx(adv748x_sd_to_csi2(sd)) ?
			 &adv748x_tx_media_ops : &adv748x_media_ops;
}