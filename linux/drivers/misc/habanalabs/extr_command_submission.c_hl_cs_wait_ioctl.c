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
struct TYPE_4__ {int /*<<< orphan*/  status; } ;
struct TYPE_3__ {int /*<<< orphan*/  timeout_us; int /*<<< orphan*/  seq; } ;
union hl_wait_cs_args {TYPE_2__ out; TYPE_1__ in; } ;
typedef  int /*<<< orphan*/  u64 ;
struct hl_fpriv {int /*<<< orphan*/  ctx; struct hl_device* hdev; } ;
struct hl_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 long EINTR ; 
 long EIO ; 
 long ERESTARTSYS ; 
 long ETIMEDOUT ; 
 int /*<<< orphan*/  HL_WAIT_CS_STATUS_ABORTED ; 
 int /*<<< orphan*/  HL_WAIT_CS_STATUS_BUSY ; 
 int /*<<< orphan*/  HL_WAIT_CS_STATUS_COMPLETED ; 
 int /*<<< orphan*/  HL_WAIT_CS_STATUS_INTERRUPTED ; 
 int /*<<< orphan*/  HL_WAIT_CS_STATUS_TIMEDOUT ; 
 long _hl_cs_wait_ioctl (struct hl_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (union hl_wait_cs_args*,int /*<<< orphan*/ ,int) ; 

int hl_cs_wait_ioctl(struct hl_fpriv *hpriv, void *data)
{
	struct hl_device *hdev = hpriv->hdev;
	union hl_wait_cs_args *args = data;
	u64 seq = args->in.seq;
	long rc;

	rc = _hl_cs_wait_ioctl(hdev, hpriv->ctx, args->in.timeout_us, seq);

	memset(args, 0, sizeof(*args));

	if (rc < 0) {
		dev_err(hdev->dev, "Error %ld on waiting for CS handle %llu\n",
			rc, seq);
		if (rc == -ERESTARTSYS) {
			args->out.status = HL_WAIT_CS_STATUS_INTERRUPTED;
			rc = -EINTR;
		} else if (rc == -ETIMEDOUT) {
			args->out.status = HL_WAIT_CS_STATUS_TIMEDOUT;
		} else if (rc == -EIO) {
			args->out.status = HL_WAIT_CS_STATUS_ABORTED;
		}
		return rc;
	}

	if (rc == 0)
		args->out.status = HL_WAIT_CS_STATUS_BUSY;
	else
		args->out.status = HL_WAIT_CS_STATUS_COMPLETED;

	return 0;
}