#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_8__ {int /*<<< orphan*/ * max_rate; } ;
struct TYPE_7__ {int enabled_tc; TYPE_1__* tc_info; } ;
struct i40e_vsi {int /*<<< orphan*/ * tc_seid_map; TYPE_5__* back; int /*<<< orphan*/  ch_list; TYPE_3__ mqprio_qopt; TYPE_2__ tc_config; int /*<<< orphan*/  seid; } ;
struct i40e_channel {int /*<<< orphan*/  seid; int /*<<< orphan*/  num_queue_pairs; int /*<<< orphan*/  list; int /*<<< orphan*/  max_tx_rate; int /*<<< orphan*/  base_queue; } ;
struct TYPE_10__ {TYPE_4__* pdev; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  qoffset; int /*<<< orphan*/  qcount; } ;

/* Variables and functions */
 int BIT (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I40E_BW_MBPS_DIVISOR ; 
 int I40E_MAX_TRAFFIC_CLASS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_div (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i40e_create_queue_channel (struct i40e_vsi*,struct i40e_channel*) ; 
 int /*<<< orphan*/  i40e_remove_queue_channels (struct i40e_vsi*) ; 
 struct i40e_channel* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int i40e_configure_queue_channels(struct i40e_vsi *vsi)
{
	struct i40e_channel *ch;
	u64 max_rate = 0;
	int ret = 0, i;

	/* Create app vsi with the TCs. Main VSI with TC0 is already set up */
	vsi->tc_seid_map[0] = vsi->seid;
	for (i = 1; i < I40E_MAX_TRAFFIC_CLASS; i++) {
		if (vsi->tc_config.enabled_tc & BIT(i)) {
			ch = kzalloc(sizeof(*ch), GFP_KERNEL);
			if (!ch) {
				ret = -ENOMEM;
				goto err_free;
			}

			INIT_LIST_HEAD(&ch->list);
			ch->num_queue_pairs =
				vsi->tc_config.tc_info[i].qcount;
			ch->base_queue =
				vsi->tc_config.tc_info[i].qoffset;

			/* Bandwidth limit through tc interface is in bytes/s,
			 * change to Mbit/s
			 */
			max_rate = vsi->mqprio_qopt.max_rate[i];
			do_div(max_rate, I40E_BW_MBPS_DIVISOR);
			ch->max_tx_rate = max_rate;

			list_add_tail(&ch->list, &vsi->ch_list);

			ret = i40e_create_queue_channel(vsi, ch);
			if (ret) {
				dev_err(&vsi->back->pdev->dev,
					"Failed creating queue channel with TC%d: queues %d\n",
					i, ch->num_queue_pairs);
				goto err_free;
			}
			vsi->tc_seid_map[i] = ch->seid;
		}
	}
	return ret;

err_free:
	i40e_remove_queue_channels(vsi);
	return ret;
}