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
struct usb_tt {struct mu3h_sch_tt** hcpriv; TYPE_1__* hub; scalar_t__ multi; } ;
struct usb_device {int ttport; struct usb_tt* tt; } ;
struct mu3h_sch_tt {unsigned int tt_port; struct usb_tt* usb_tt; int /*<<< orphan*/  ep_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  maxchild; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct mu3h_sch_tt* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct mu3h_sch_tt** kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mu3h_sch_tt**) ; 
 struct mu3h_sch_tt* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mu3h_sch_tt *find_tt(struct usb_device *udev)
{
	struct usb_tt *utt = udev->tt;
	struct mu3h_sch_tt *tt, **tt_index, **ptt;
	unsigned int port;
	bool allocated_index = false;

	if (!utt)
		return NULL;	/* Not below a TT */

	/*
	 * Find/create our data structure.
	 * For hubs with a single TT, we get it directly.
	 * For hubs with multiple TTs, there's an extra level of pointers.
	 */
	tt_index = NULL;
	if (utt->multi) {
		tt_index = utt->hcpriv;
		if (!tt_index) {	/* Create the index array */
			tt_index = kcalloc(utt->hub->maxchild,
					sizeof(*tt_index), GFP_KERNEL);
			if (!tt_index)
				return ERR_PTR(-ENOMEM);
			utt->hcpriv = tt_index;
			allocated_index = true;
		}
		port = udev->ttport - 1;
		ptt = &tt_index[port];
	} else {
		port = 0;
		ptt = (struct mu3h_sch_tt **) &utt->hcpriv;
	}

	tt = *ptt;
	if (!tt) {	/* Create the mu3h_sch_tt */
		tt = kzalloc(sizeof(*tt), GFP_KERNEL);
		if (!tt) {
			if (allocated_index) {
				utt->hcpriv = NULL;
				kfree(tt_index);
			}
			return ERR_PTR(-ENOMEM);
		}
		INIT_LIST_HEAD(&tt->ep_list);
		tt->usb_tt = utt;
		tt->tt_port = port;
		*ptt = tt;
	}

	return tt;
}