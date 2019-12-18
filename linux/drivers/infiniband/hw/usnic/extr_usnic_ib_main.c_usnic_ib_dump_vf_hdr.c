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
struct usnic_ib_vf {TYPE_2__* pf; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {TYPE_1__ ib_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int scnprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usnic_ib_dump_vf_hdr(void *obj, char *buf, int buf_sz)
{
	struct usnic_ib_vf *vf = obj;
	return scnprintf(buf, buf_sz, "PF: %s ", dev_name(&vf->pf->ib_dev.dev));
}