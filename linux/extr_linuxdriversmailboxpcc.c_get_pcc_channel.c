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
struct mbox_chan {int dummy; } ;
struct TYPE_2__ {int num_chans; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 struct mbox_chan* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct mbox_chan* pcc_mbox_channels ; 
 TYPE_1__ pcc_mbox_ctrl ; 

__attribute__((used)) static struct mbox_chan *get_pcc_channel(int id)
{
	if (id < 0 || id >= pcc_mbox_ctrl.num_chans)
		return ERR_PTR(-ENOENT);

	return &pcc_mbox_channels[id];
}