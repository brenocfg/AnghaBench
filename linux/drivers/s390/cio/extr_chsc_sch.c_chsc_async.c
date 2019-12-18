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
struct TYPE_10__ {int /*<<< orphan*/  sch_no; int /*<<< orphan*/  ssid; } ;
struct TYPE_7__ {int /*<<< orphan*/  fctl; } ;
struct TYPE_8__ {TYPE_2__ cmd; } ;
struct TYPE_9__ {TYPE_3__ scsw; } ;
struct subchannel {int /*<<< orphan*/  dev; TYPE_5__ schid; int /*<<< orphan*/  lock; TYPE_4__ schib; } ;
struct chsc_request {int dummy; } ;
struct chsc_private {struct chsc_request* request; } ;
struct TYPE_6__ {int key; TYPE_5__ sid; } ;
struct chsc_async_area {TYPE_1__ header; } ;
typedef  int /*<<< orphan*/  dbf ;

/* Variables and functions */
 int /*<<< orphan*/  CHSC_LOG (int,char*) ; 
 int /*<<< orphan*/  CHSC_LOG_HEX (int,TYPE_5__*,int) ; 
 int /*<<< orphan*/  CHSC_MSG (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int EBUSY ; 
 int EINPROGRESS ; 
 int ENODEV ; 
 int PAGE_DEFAULT_KEY ; 
 int /*<<< orphan*/  SCSW_FCTL_START_FUNC ; 
 int chsc (struct chsc_async_area*) ; 
 struct subchannel* chsc_get_next_subchannel (struct subchannel*) ; 
 struct chsc_private* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int chsc_async(struct chsc_async_area *chsc_area,
		      struct chsc_request *request)
{
	int cc;
	struct chsc_private *private;
	struct subchannel *sch = NULL;
	int ret = -ENODEV;
	char dbf[10];

	chsc_area->header.key = PAGE_DEFAULT_KEY >> 4;
	while ((sch = chsc_get_next_subchannel(sch))) {
		spin_lock(sch->lock);
		private = dev_get_drvdata(&sch->dev);
		if (private->request) {
			spin_unlock(sch->lock);
			ret = -EBUSY;
			continue;
		}
		chsc_area->header.sid = sch->schid;
		CHSC_LOG(2, "schid");
		CHSC_LOG_HEX(2, &sch->schid, sizeof(sch->schid));
		cc = chsc(chsc_area);
		snprintf(dbf, sizeof(dbf), "cc:%d", cc);
		CHSC_LOG(2, dbf);
		switch (cc) {
		case 0:
			ret = 0;
			break;
		case 1:
			sch->schib.scsw.cmd.fctl |= SCSW_FCTL_START_FUNC;
			ret = -EINPROGRESS;
			private->request = request;
			break;
		case 2:
			ret = -EBUSY;
			break;
		default:
			ret = -ENODEV;
		}
		spin_unlock(sch->lock);
		CHSC_MSG(2, "chsc on 0.%x.%04x returned cc=%d\n",
			 sch->schid.ssid, sch->schid.sch_no, cc);
		if (ret == -EINPROGRESS)
			return -EINPROGRESS;
		put_device(&sch->dev);
		if (ret == 0)
			return 0;
	}
	return ret;
}