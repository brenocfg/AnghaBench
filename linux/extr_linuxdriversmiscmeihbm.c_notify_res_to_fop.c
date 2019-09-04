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
struct mei_hbm_cl_cmd {int dummy; } ;
struct hbm_notification_response {int /*<<< orphan*/  start; } ;
typedef  enum mei_cb_file_ops { ____Placeholder_mei_cb_file_ops } mei_cb_file_ops ;

/* Variables and functions */
 int mei_cl_notify_req2fop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline enum mei_cb_file_ops notify_res_to_fop(struct mei_hbm_cl_cmd *cmd)
{
	struct hbm_notification_response *rs =
		(struct hbm_notification_response *)cmd;

	return mei_cl_notify_req2fop(rs->start);
}