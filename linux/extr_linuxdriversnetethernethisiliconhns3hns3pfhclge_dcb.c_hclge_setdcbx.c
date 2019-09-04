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
typedef  int u8 ;
struct hnae3_handle {int dummy; } ;
struct hclge_vport {struct hclge_dev* back; } ;
struct hclge_dev {int dcbx_cap; } ;

/* Variables and functions */
 int DCB_CAP_DCBX_HOST ; 
 int DCB_CAP_DCBX_LLD_MANAGED ; 
 int DCB_CAP_DCBX_VER_CEE ; 
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 

__attribute__((used)) static u8 hclge_setdcbx(struct hnae3_handle *h, u8 mode)
{
	struct hclge_vport *vport = hclge_get_vport(h);
	struct hclge_dev *hdev = vport->back;

	/* No support for LLD_MANAGED modes or CEE */
	if ((mode & DCB_CAP_DCBX_LLD_MANAGED) ||
	    (mode & DCB_CAP_DCBX_VER_CEE) ||
	    !(mode & DCB_CAP_DCBX_HOST))
		return 1;

	hdev->dcbx_cap = mode;

	return 0;
}