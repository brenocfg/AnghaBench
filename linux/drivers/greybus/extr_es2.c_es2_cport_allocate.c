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
struct ida {int dummy; } ;
struct gb_host_device {int num_cports; int /*<<< orphan*/  dev; struct ida cport_id_map; } ;
struct es2_ap_dev {int cdsi1_in_use; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
#define  ES2_CPORT_CDSI0 129 
#define  ES2_CPORT_CDSI1 128 
 unsigned long GB_CONNECTION_FLAG_CDSI1 ; 
 unsigned long GB_CONNECTION_FLAG_OFFLOADED ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct es2_ap_dev* hd_to_es2 (struct gb_host_device*) ; 
 int ida_simple_get (struct ida*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int es2_cport_allocate(struct gb_host_device *hd, int cport_id,
			      unsigned long flags)
{
	struct es2_ap_dev *es2 = hd_to_es2(hd);
	struct ida *id_map = &hd->cport_id_map;
	int ida_start, ida_end;

	switch (cport_id) {
	case ES2_CPORT_CDSI0:
	case ES2_CPORT_CDSI1:
		dev_err(&hd->dev, "cport %d not available\n", cport_id);
		return -EBUSY;
	}

	if (flags & GB_CONNECTION_FLAG_OFFLOADED &&
	    flags & GB_CONNECTION_FLAG_CDSI1) {
		if (es2->cdsi1_in_use) {
			dev_err(&hd->dev, "CDSI1 already in use\n");
			return -EBUSY;
		}

		es2->cdsi1_in_use = true;

		return ES2_CPORT_CDSI1;
	}

	if (cport_id < 0) {
		ida_start = 0;
		ida_end = hd->num_cports;
	} else if (cport_id < hd->num_cports) {
		ida_start = cport_id;
		ida_end = cport_id + 1;
	} else {
		dev_err(&hd->dev, "cport %d not available\n", cport_id);
		return -EINVAL;
	}

	return ida_simple_get(id_map, ida_start, ida_end, GFP_KERNEL);
}