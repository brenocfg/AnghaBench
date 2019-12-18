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
struct rio_mport {int dummy; } ;
struct cm_dev {int /*<<< orphan*/  mport; } ;

/* Variables and functions */
 scalar_t__ rio_mport_is_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rio_txcq_handler (struct cm_dev*,int) ; 

__attribute__((used)) static void riocm_outb_msg_event(struct rio_mport *mport, void *dev_id,
				 int mbox, int slot)
{
	struct cm_dev *cm = dev_id;

	if (cm && rio_mport_is_running(cm->mport))
		rio_txcq_handler(cm, slot);
}