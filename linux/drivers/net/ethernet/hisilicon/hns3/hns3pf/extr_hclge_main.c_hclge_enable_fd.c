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
struct hnae3_handle {int dummy; } ;
struct hclge_vport {struct hclge_dev* back; } ;
struct hclge_dev {int fd_en; scalar_t__ fd_active_type; } ;

/* Variables and functions */
 scalar_t__ HCLGE_FD_ARFS_ACTIVE ; 
 int /*<<< orphan*/  hclge_del_all_fd_entries (struct hnae3_handle*,int) ; 
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 
 int /*<<< orphan*/  hclge_restore_fd_entries (struct hnae3_handle*) ; 

__attribute__((used)) static void hclge_enable_fd(struct hnae3_handle *handle, bool enable)
{
	struct hclge_vport *vport = hclge_get_vport(handle);
	struct hclge_dev *hdev = vport->back;
	bool clear;

	hdev->fd_en = enable;
	clear = hdev->fd_active_type == HCLGE_FD_ARFS_ACTIVE;
	if (!enable)
		hclge_del_all_fd_entries(handle, clear);
	else
		hclge_restore_fd_entries(handle);
}