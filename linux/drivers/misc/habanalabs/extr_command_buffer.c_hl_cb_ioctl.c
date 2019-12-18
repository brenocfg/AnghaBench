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
struct TYPE_6__ {int op; int /*<<< orphan*/  cb_handle; int /*<<< orphan*/  cb_size; } ;
struct TYPE_5__ {int /*<<< orphan*/  cb_handle; } ;
union hl_cb_args {TYPE_3__ in; TYPE_2__ out; } ;
typedef  int /*<<< orphan*/  u64 ;
struct hl_fpriv {int /*<<< orphan*/  cb_mgr; TYPE_1__* ctx; struct hl_device* hdev; } ;
struct hl_device {int /*<<< orphan*/  in_reset; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  asid; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOTTY ; 
#define  HL_CB_OP_CREATE 129 
#define  HL_CB_OP_DESTROY 128 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn_ratelimited (int /*<<< orphan*/ ,char*,char*) ; 
 int hl_cb_create (struct hl_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int hl_cb_destroy (struct hl_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ hl_device_disabled_or_in_reset (struct hl_device*) ; 
 int /*<<< orphan*/  memset (union hl_cb_args*,int /*<<< orphan*/ ,int) ; 

int hl_cb_ioctl(struct hl_fpriv *hpriv, void *data)
{
	union hl_cb_args *args = data;
	struct hl_device *hdev = hpriv->hdev;
	u64 handle;
	int rc;

	if (hl_device_disabled_or_in_reset(hdev)) {
		dev_warn_ratelimited(hdev->dev,
			"Device is %s. Can't execute CB IOCTL\n",
			atomic_read(&hdev->in_reset) ? "in_reset" : "disabled");
		return -EBUSY;
	}

	switch (args->in.op) {
	case HL_CB_OP_CREATE:
		rc = hl_cb_create(hdev, &hpriv->cb_mgr, args->in.cb_size,
					&handle, hpriv->ctx->asid);
		memset(args, 0, sizeof(*args));
		args->out.cb_handle = handle;
		break;
	case HL_CB_OP_DESTROY:
		rc = hl_cb_destroy(hdev, &hpriv->cb_mgr,
					args->in.cb_handle);
		break;
	default:
		rc = -ENOTTY;
		break;
	}

	return rc;
}