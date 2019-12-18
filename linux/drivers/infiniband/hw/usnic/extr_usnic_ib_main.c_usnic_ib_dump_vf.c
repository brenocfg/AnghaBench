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
struct usnic_ib_vf {int /*<<< orphan*/  vnic; } ;

/* Variables and functions */
 int /*<<< orphan*/  usnic_ib_dump_vf_hdr ; 
 int /*<<< orphan*/  usnic_ib_qp_grp_dump_hdr ; 
 int /*<<< orphan*/  usnic_ib_qp_grp_dump_rows ; 
 int /*<<< orphan*/  usnic_vnic_dump (int /*<<< orphan*/ ,char*,int,struct usnic_ib_vf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usnic_ib_dump_vf(struct usnic_ib_vf *vf, char *buf, int buf_sz)
{
	usnic_vnic_dump(vf->vnic, buf, buf_sz, vf,
			usnic_ib_dump_vf_hdr,
			usnic_ib_qp_grp_dump_hdr, usnic_ib_qp_grp_dump_rows);
}