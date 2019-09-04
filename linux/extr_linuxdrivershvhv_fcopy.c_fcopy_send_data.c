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
typedef  int /*<<< orphan*/  wchar_t ;
struct work_struct {int dummy; } ;
struct TYPE_4__ {int operation; } ;
struct hv_start_fcopy {int /*<<< orphan*/  file_size; int /*<<< orphan*/  copy_flags; scalar_t__ path_name; scalar_t__ file_name; TYPE_1__ hdr; } ;
struct hv_do_fcopy {int dummy; } ;
typedef  int /*<<< orphan*/  __u8 ;
struct TYPE_6__ {int recv_len; int /*<<< orphan*/  state; TYPE_2__* fcopy_msg; } ;
struct TYPE_5__ {int operation; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HVUTIL_READY ; 
 int /*<<< orphan*/  HVUTIL_USERSPACE_REQ ; 
 int /*<<< orphan*/  HV_E_FAIL ; 
#define  START_FILE_COPY 129 
 int /*<<< orphan*/  UTF16_LITTLE_ENDIAN ; 
#define  WRITE_TO_FILE 128 
 int /*<<< orphan*/  W_MAX_PATH ; 
 scalar_t__ cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fcopy_respond_to_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fcopy_timeout_work ; 
 TYPE_3__ fcopy_transaction ; 
 int /*<<< orphan*/  hvt ; 
 int hvutil_transport_send (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct hv_start_fcopy*) ; 
 struct hv_start_fcopy* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  utf16s_to_utf8s (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fcopy_send_data(struct work_struct *dummy)
{
	struct hv_start_fcopy *smsg_out = NULL;
	int operation = fcopy_transaction.fcopy_msg->operation;
	struct hv_start_fcopy *smsg_in;
	void *out_src;
	int rc, out_len;

	/*
	 * The  strings sent from the host are encoded in
	 * in utf16; convert it to utf8 strings.
	 * The host assures us that the utf16 strings will not exceed
	 * the max lengths specified. We will however, reserve room
	 * for the string terminating character - in the utf16s_utf8s()
	 * function we limit the size of the buffer where the converted
	 * string is placed to W_MAX_PATH -1 to guarantee
	 * that the strings can be properly terminated!
	 */

	switch (operation) {
	case START_FILE_COPY:
		out_len = sizeof(struct hv_start_fcopy);
		smsg_out = kzalloc(sizeof(*smsg_out), GFP_KERNEL);
		if (!smsg_out)
			return;

		smsg_out->hdr.operation = operation;
		smsg_in = (struct hv_start_fcopy *)fcopy_transaction.fcopy_msg;

		utf16s_to_utf8s((wchar_t *)smsg_in->file_name, W_MAX_PATH,
				UTF16_LITTLE_ENDIAN,
				(__u8 *)&smsg_out->file_name, W_MAX_PATH - 1);

		utf16s_to_utf8s((wchar_t *)smsg_in->path_name, W_MAX_PATH,
				UTF16_LITTLE_ENDIAN,
				(__u8 *)&smsg_out->path_name, W_MAX_PATH - 1);

		smsg_out->copy_flags = smsg_in->copy_flags;
		smsg_out->file_size = smsg_in->file_size;
		out_src = smsg_out;
		break;

	case WRITE_TO_FILE:
		out_src = fcopy_transaction.fcopy_msg;
		out_len = sizeof(struct hv_do_fcopy);
		break;
	default:
		out_src = fcopy_transaction.fcopy_msg;
		out_len = fcopy_transaction.recv_len;
		break;
	}

	fcopy_transaction.state = HVUTIL_USERSPACE_REQ;
	rc = hvutil_transport_send(hvt, out_src, out_len, NULL);
	if (rc) {
		pr_debug("FCP: failed to communicate to the daemon: %d\n", rc);
		if (cancel_delayed_work_sync(&fcopy_timeout_work)) {
			fcopy_respond_to_host(HV_E_FAIL);
			fcopy_transaction.state = HVUTIL_READY;
		}
	}
	kfree(smsg_out);
}