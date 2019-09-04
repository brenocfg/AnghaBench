#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  entity; } ;
struct rvin_dev {TYPE_2__ pad; TYPE_1__ vdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEDIA_PAD_FL_SINK ; 
 int media_entity_pads_init (int /*<<< orphan*/ *,int,TYPE_2__*) ; 
 int rvin_group_get (struct rvin_dev*) ; 
 int /*<<< orphan*/  rvin_group_put (struct rvin_dev*) ; 
 int rvin_mc_parse_of_graph (struct rvin_dev*) ; 

__attribute__((used)) static int rvin_mc_init(struct rvin_dev *vin)
{
	int ret;

	vin->pad.flags = MEDIA_PAD_FL_SINK;
	ret = media_entity_pads_init(&vin->vdev.entity, 1, &vin->pad);
	if (ret)
		return ret;

	ret = rvin_group_get(vin);
	if (ret)
		return ret;

	ret = rvin_mc_parse_of_graph(vin);
	if (ret)
		rvin_group_put(vin);

	return ret;
}