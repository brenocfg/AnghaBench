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
struct rbd_obj_request {int /*<<< orphan*/  osd_req; } ;
struct page {int dummy; } ;
struct ceph_timespec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_OSD_OP_STAT ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 scalar_t__ IS_ERR (struct page**) ; 
 int PTR_ERR (struct page**) ; 
 struct page** ceph_alloc_page_vector (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osd_req_op_init (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osd_req_op_raw_data_in_pages (int /*<<< orphan*/ ,unsigned int,struct page**,int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int __rbd_obj_setup_stat(struct rbd_obj_request *obj_req,
				unsigned int which)
{
	struct page **pages;

	/*
	 * The response data for a STAT call consists of:
	 *     le64 length;
	 *     struct {
	 *         le32 tv_sec;
	 *         le32 tv_nsec;
	 *     } mtime;
	 */
	pages = ceph_alloc_page_vector(1, GFP_NOIO);
	if (IS_ERR(pages))
		return PTR_ERR(pages);

	osd_req_op_init(obj_req->osd_req, which, CEPH_OSD_OP_STAT, 0);
	osd_req_op_raw_data_in_pages(obj_req->osd_req, which, pages,
				     8 + sizeof(struct ceph_timespec),
				     0, false, true);
	return 0;
}