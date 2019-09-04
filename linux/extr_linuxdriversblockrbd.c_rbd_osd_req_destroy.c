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
struct ceph_osd_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ceph_osdc_put_request (struct ceph_osd_request*) ; 

__attribute__((used)) static void rbd_osd_req_destroy(struct ceph_osd_request *osd_req)
{
	ceph_osdc_put_request(osd_req);
}