#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pvr2_v4l2_dev {int config; int /*<<< orphan*/  devbase; int /*<<< orphan*/ * stream; TYPE_3__* v4lp; int /*<<< orphan*/  minor_type; } ;
struct pvr2_hdw {int dummy; } ;
typedef  int /*<<< orphan*/  msg ;
typedef  enum pvr2_config { ____Placeholder_pvr2_config } pvr2_config ;
struct TYPE_5__ {TYPE_1__* mc_head; } ;
struct TYPE_6__ {TYPE_2__ channel; } ;
struct TYPE_4__ {struct pvr2_hdw* hdw; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_info (char*,char*) ; 
 int /*<<< orphan*/  pvr2_config_get_name (int) ; 
 int /*<<< orphan*/  pvr2_hdw_v4l_store_minor_number (struct pvr2_hdw*,int /*<<< orphan*/ ,int) ; 
 unsigned int scnprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_device_node_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pvr2_v4l2_dev_destroy(struct pvr2_v4l2_dev *dip)
{
	struct pvr2_hdw *hdw = dip->v4lp->channel.mc_head->hdw;
	enum pvr2_config cfg = dip->config;
	char msg[80];
	unsigned int mcnt;

	/* Construct the unregistration message *before* we actually
	   perform the unregistration step.  By doing it this way we don't
	   have to worry about potentially touching deleted resources. */
	mcnt = scnprintf(msg, sizeof(msg) - 1,
			 "pvrusb2: unregistered device %s [%s]",
			 video_device_node_name(&dip->devbase),
			 pvr2_config_get_name(cfg));
	msg[mcnt] = 0;

	pvr2_hdw_v4l_store_minor_number(hdw,dip->minor_type,-1);

	/* Paranoia */
	dip->v4lp = NULL;
	dip->stream = NULL;

	/* Actual deallocation happens later when all internal references
	   are gone. */
	video_unregister_device(&dip->devbase);

	pr_info("%s\n", msg);

}