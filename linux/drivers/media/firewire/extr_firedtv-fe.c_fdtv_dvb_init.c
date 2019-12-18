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
struct TYPE_2__ {int /*<<< orphan*/  num; } ;
struct firedtv {int /*<<< orphan*/  device; int /*<<< orphan*/  isochannel; int /*<<< orphan*/  subunit; TYPE_1__ adapter; } ;
struct dvb_frontend {struct firedtv* sec_priv; } ;

/* Variables and functions */
 int cmp_establish_pp_connection (struct firedtv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int fdtv_start_iso (struct firedtv*) ; 

__attribute__((used)) static int fdtv_dvb_init(struct dvb_frontend *fe)
{
	struct firedtv *fdtv = fe->sec_priv;
	int err;

	/* FIXME - allocate free channel at IRM */
	fdtv->isochannel = fdtv->adapter.num;

	err = cmp_establish_pp_connection(fdtv, fdtv->subunit,
					  fdtv->isochannel);
	if (err) {
		dev_err(fdtv->device,
			"could not establish point to point connection\n");
		return err;
	}

	return fdtv_start_iso(fdtv);
}