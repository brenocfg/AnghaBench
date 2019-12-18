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
typedef  int /*<<< orphan*/  u32 ;
struct rio_dev {int pef; size_t destid; TYPE_1__* rswitch; struct rio_dev* prev; } ;
struct TYPE_2__ {int* route_table; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  RIO_DEV_ID_CAR ; 
 int RIO_INVALID_ROUTE ; 
 int RIO_PEF_SWITCH ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  rio_name (struct rio_dev*) ; 
 int /*<<< orphan*/  rio_read_config_32 (struct rio_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
rio_chk_dev_route(struct rio_dev *rdev, struct rio_dev **nrdev, int *npnum)
{
	u32 result;
	int p_port, rc = -EIO;
	struct rio_dev *prev = NULL;

	/* Find switch with failed RIO link */
	while (rdev->prev && (rdev->prev->pef & RIO_PEF_SWITCH)) {
		if (!rio_read_config_32(rdev->prev, RIO_DEV_ID_CAR, &result)) {
			prev = rdev->prev;
			break;
		}
		rdev = rdev->prev;
	}

	if (!prev)
		goto err_out;

	p_port = prev->rswitch->route_table[rdev->destid];

	if (p_port != RIO_INVALID_ROUTE) {
		pr_debug("RIO: link failed on [%s]-P%d\n",
			 rio_name(prev), p_port);
		*nrdev = prev;
		*npnum = p_port;
		rc = 0;
	} else
		pr_debug("RIO: failed to trace route to %s\n", rio_name(rdev));
err_out:
	return rc;
}