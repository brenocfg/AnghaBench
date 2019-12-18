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
typedef  int /*<<< orphan*/  transition_ver ;
struct usb_interface {TYPE_3__* cur_altsetting; } ;
struct usb_device {int dummy; } ;
struct uclogic_params {int pen_frame_flag; int /*<<< orphan*/  frame; int /*<<< orphan*/  pen; int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct hid_device {TYPE_1__ dev; } ;
typedef  int /*<<< orphan*/  p ;
typedef  scalar_t__ __u8 ;
struct TYPE_5__ {scalar_t__ bInterfaceNumber; } ;
struct TYPE_6__ {TYPE_2__ desc; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EPIPE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  UCLOGIC_RDESC_BUTTONPAD_V2_ID ; 
 int /*<<< orphan*/  hid_dbg (struct hid_device*,char*,...) ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*,int) ; 
 struct usb_device* hid_to_usb_dev (struct hid_device*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kzalloc (size_t const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct uclogic_params*,struct uclogic_params*,int) ; 
 int /*<<< orphan*/  memset (struct uclogic_params*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 struct usb_interface* to_usb_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uclogic_params_cleanup (struct uclogic_params*) ; 
 int uclogic_params_frame_init_v1_buttonpad (int /*<<< orphan*/ *,int*,struct hid_device*) ; 
 int uclogic_params_frame_init_with_desc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uclogic_params_init_invalid (struct uclogic_params*) ; 
 int /*<<< orphan*/  uclogic_params_init_with_pen_unused (struct uclogic_params*) ; 
 int uclogic_params_pen_init_v1 (int /*<<< orphan*/ *,int*,struct hid_device*) ; 
 int uclogic_params_pen_init_v2 (int /*<<< orphan*/ *,int*,struct hid_device*) ; 
 int /*<<< orphan*/  uclogic_rdesc_buttonpad_v2_arr ; 
 int /*<<< orphan*/  uclogic_rdesc_buttonpad_v2_size ; 
 int usb_string (struct usb_device*,int,char*,size_t const) ; 

__attribute__((used)) static int uclogic_params_huion_init(struct uclogic_params *params,
				     struct hid_device *hdev)
{
	int rc;
	struct usb_device *udev = hid_to_usb_dev(hdev);
	struct usb_interface *iface = to_usb_interface(hdev->dev.parent);
	__u8 bInterfaceNumber = iface->cur_altsetting->desc.bInterfaceNumber;
	bool found;
	/* The resulting parameters (noop) */
	struct uclogic_params p = {0, };
	static const char transition_ver[] = "HUION_T153_160607";
	char *ver_ptr = NULL;
	const size_t ver_len = sizeof(transition_ver) + 1;

	/* Check arguments */
	if (params == NULL || hdev == NULL) {
		rc = -EINVAL;
		goto cleanup;
	}

	/* If it's not a pen interface */
	if (bInterfaceNumber != 0) {
		/* TODO: Consider marking the interface invalid */
		uclogic_params_init_with_pen_unused(&p);
		goto output;
	}

	/* Try to get firmware version */
	ver_ptr = kzalloc(ver_len, GFP_KERNEL);
	if (ver_ptr == NULL) {
		rc = -ENOMEM;
		goto cleanup;
	}
	rc = usb_string(udev, 201, ver_ptr, ver_len);
	if (rc == -EPIPE) {
		*ver_ptr = '\0';
	} else if (rc < 0) {
		hid_err(hdev,
			"failed retrieving Huion firmware version: %d\n", rc);
		goto cleanup;
	}

	/* If this is a transition firmware */
	if (strcmp(ver_ptr, transition_ver) == 0) {
		hid_dbg(hdev,
			"transition firmware detected, not probing pen v2 parameters\n");
	} else {
		/* Try to probe v2 pen parameters */
		rc = uclogic_params_pen_init_v2(&p.pen, &found, hdev);
		if (rc != 0) {
			hid_err(hdev,
				"failed probing pen v2 parameters: %d\n", rc);
			goto cleanup;
		} else if (found) {
			hid_dbg(hdev, "pen v2 parameters found\n");
			/* Create v2 buttonpad parameters */
			rc = uclogic_params_frame_init_with_desc(
					&p.frame,
					uclogic_rdesc_buttonpad_v2_arr,
					uclogic_rdesc_buttonpad_v2_size,
					UCLOGIC_RDESC_BUTTONPAD_V2_ID);
			if (rc != 0) {
				hid_err(hdev,
					"failed creating v2 buttonpad parameters: %d\n",
					rc);
				goto cleanup;
			}
			/* Set bitmask marking frame reports in pen reports */
			p.pen_frame_flag = 0x20;
			goto output;
		}
		hid_dbg(hdev, "pen v2 parameters not found\n");
	}

	/* Try to probe v1 pen parameters */
	rc = uclogic_params_pen_init_v1(&p.pen, &found, hdev);
	if (rc != 0) {
		hid_err(hdev,
			"failed probing pen v1 parameters: %d\n", rc);
		goto cleanup;
	} else if (found) {
		hid_dbg(hdev, "pen v1 parameters found\n");
		/* Try to probe v1 buttonpad */
		rc = uclogic_params_frame_init_v1_buttonpad(
						&p.frame,
						&found, hdev);
		if (rc != 0) {
			hid_err(hdev, "v1 buttonpad probing failed: %d\n", rc);
			goto cleanup;
		}
		hid_dbg(hdev, "buttonpad v1 parameters%s found\n",
			(found ? "" : " not"));
		if (found) {
			/* Set bitmask marking frame reports */
			p.pen_frame_flag = 0x20;
		}
		goto output;
	}
	hid_dbg(hdev, "pen v1 parameters not found\n");

	uclogic_params_init_invalid(&p);

output:
	/* Output parameters */
	memcpy(params, &p, sizeof(*params));
	memset(&p, 0, sizeof(p));
	rc = 0;
cleanup:
	kfree(ver_ptr);
	uclogic_params_cleanup(&p);
	return rc;
}