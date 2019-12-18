#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct synthvid_version_req {int dummy; } ;
struct synthvid_msg_hdr {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  is_accepted; } ;
struct TYPE_5__ {void* version; } ;
struct TYPE_4__ {int size; int /*<<< orphan*/  type; } ;
struct synthvid_msg {TYPE_3__ ver_resp; TYPE_2__ ver_req; TYPE_1__ vid_hdr; } ;
struct hvfb_par {void* synthvid_version; int /*<<< orphan*/  wait; scalar_t__ init_buf; } ;
struct hv_device {int dummy; } ;
struct fb_info {struct hvfb_par* par; } ;

/* Variables and functions */
 int ENODEV ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  SYNTHVID_VERSION_REQUEST ; 
 int /*<<< orphan*/  VSP_TIMEOUT ; 
 struct fb_info* hv_get_drvdata (struct hv_device*) ; 
 int /*<<< orphan*/  memset (struct synthvid_msg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  synthvid_send (struct hv_device*,struct synthvid_msg*) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int synthvid_negotiate_ver(struct hv_device *hdev, u32 ver)
{
	struct fb_info *info = hv_get_drvdata(hdev);
	struct hvfb_par *par = info->par;
	struct synthvid_msg *msg = (struct synthvid_msg *)par->init_buf;
	int ret = 0;
	unsigned long t;

	memset(msg, 0, sizeof(struct synthvid_msg));
	msg->vid_hdr.type = SYNTHVID_VERSION_REQUEST;
	msg->vid_hdr.size = sizeof(struct synthvid_msg_hdr) +
		sizeof(struct synthvid_version_req);
	msg->ver_req.version = ver;
	synthvid_send(hdev, msg);

	t = wait_for_completion_timeout(&par->wait, VSP_TIMEOUT);
	if (!t) {
		pr_err("Time out on waiting version response\n");
		ret = -ETIMEDOUT;
		goto out;
	}
	if (!msg->ver_resp.is_accepted) {
		ret = -ENODEV;
		goto out;
	}

	par->synthvid_version = ver;

out:
	return ret;
}