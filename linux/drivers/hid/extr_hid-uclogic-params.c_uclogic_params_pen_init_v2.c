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
struct uclogic_params_pen {int* desc_ptr; int fragmented_hires; int /*<<< orphan*/  inrange; int /*<<< orphan*/  id; int /*<<< orphan*/  desc_size; } ;
struct hid_device {int dummy; } ;
typedef  int s32 ;
typedef  int __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EPIPE ; 
 int /*<<< orphan*/  UCLOGIC_PARAMS_PEN_INRANGE_NONE ; 
 int UCLOGIC_RDESC_PEN_PH_ID_NUM ; 
 size_t UCLOGIC_RDESC_PEN_PH_ID_PRESSURE_LM ; 
 size_t UCLOGIC_RDESC_PEN_PH_ID_X_LM ; 
 size_t UCLOGIC_RDESC_PEN_PH_ID_X_PM ; 
 size_t UCLOGIC_RDESC_PEN_PH_ID_Y_LM ; 
 size_t UCLOGIC_RDESC_PEN_PH_ID_Y_PM ; 
 int /*<<< orphan*/  UCLOGIC_RDESC_PEN_V2_ID ; 
 int get_unaligned_le16 (int*) ; 
 int /*<<< orphan*/  hid_dbg (struct hid_device*,char*,...) ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*,int) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int /*<<< orphan*/  memset (struct uclogic_params_pen*,int /*<<< orphan*/ ,int) ; 
 int uclogic_params_get_le24 (int*) ; 
 int uclogic_params_get_str_desc (int**,struct hid_device*,int,int const) ; 
 int /*<<< orphan*/  uclogic_rdesc_pen_v2_template_arr ; 
 int /*<<< orphan*/  uclogic_rdesc_pen_v2_template_size ; 
 int* uclogic_rdesc_template_apply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uclogic_params_pen_init_v2(struct uclogic_params_pen *pen,
					bool *pfound,
					struct hid_device *hdev)
{
	int rc;
	bool found = false;
	/* Buffer for (part of) the string descriptor */
	__u8 *buf = NULL;
	/* Descriptor length required */
	const int len = 18;
	s32 resolution;
	/* Pen report descriptor template parameters */
	s32 desc_params[UCLOGIC_RDESC_PEN_PH_ID_NUM];
	__u8 *desc_ptr = NULL;

	/* Check arguments */
	if (pen == NULL || pfound == NULL || hdev == NULL) {
		rc = -EINVAL;
		goto cleanup;
	}

	/*
	 * Read string descriptor containing pen input parameters.
	 * The specific string descriptor and data were discovered by sniffing
	 * the Windows driver traffic.
	 * NOTE: This enables fully-functional tablet mode.
	 */
	rc = uclogic_params_get_str_desc(&buf, hdev, 200, len);
	if (rc == -EPIPE) {
		hid_dbg(hdev,
			"string descriptor with pen parameters not found, assuming not compatible\n");
		goto finish;
	} else if (rc < 0) {
		hid_err(hdev, "failed retrieving pen parameters: %d\n", rc);
		goto cleanup;
	} else if (rc != len) {
		hid_dbg(hdev,
			"string descriptor with pen parameters has invalid length (got %d, expected %d), assuming not compatible\n",
			rc, len);
		goto finish;
	} else {
		size_t i;
		/*
		 * Check it's not just a catch-all UTF-16LE-encoded ASCII
		 * string (such as the model name) some tablets put into all
		 * unknown string descriptors.
		 */
		for (i = 2;
		     i < len &&
			(buf[i] >= 0x20 && buf[i] < 0x7f && buf[i + 1] == 0);
		     i += 2);
		if (i >= len) {
			hid_dbg(hdev,
				"string descriptor with pen parameters seems to contain only text, assuming not compatible\n");
			goto finish;
		}
	}

	/*
	 * Fill report descriptor parameters from the string descriptor
	 */
	desc_params[UCLOGIC_RDESC_PEN_PH_ID_X_LM] =
		uclogic_params_get_le24(buf + 2);
	desc_params[UCLOGIC_RDESC_PEN_PH_ID_Y_LM] =
		uclogic_params_get_le24(buf + 5);
	desc_params[UCLOGIC_RDESC_PEN_PH_ID_PRESSURE_LM] =
		get_unaligned_le16(buf + 8);
	resolution = get_unaligned_le16(buf + 10);
	if (resolution == 0) {
		desc_params[UCLOGIC_RDESC_PEN_PH_ID_X_PM] = 0;
		desc_params[UCLOGIC_RDESC_PEN_PH_ID_Y_PM] = 0;
	} else {
		desc_params[UCLOGIC_RDESC_PEN_PH_ID_X_PM] =
			desc_params[UCLOGIC_RDESC_PEN_PH_ID_X_LM] * 1000 /
			resolution;
		desc_params[UCLOGIC_RDESC_PEN_PH_ID_Y_PM] =
			desc_params[UCLOGIC_RDESC_PEN_PH_ID_Y_LM] * 1000 /
			resolution;
	}
	kfree(buf);
	buf = NULL;

	/*
	 * Generate pen report descriptor
	 */
	desc_ptr = uclogic_rdesc_template_apply(
				uclogic_rdesc_pen_v2_template_arr,
				uclogic_rdesc_pen_v2_template_size,
				desc_params, ARRAY_SIZE(desc_params));
	if (desc_ptr == NULL) {
		rc = -ENOMEM;
		goto cleanup;
	}

	/*
	 * Fill-in the parameters
	 */
	memset(pen, 0, sizeof(*pen));
	pen->desc_ptr = desc_ptr;
	desc_ptr = NULL;
	pen->desc_size = uclogic_rdesc_pen_v2_template_size;
	pen->id = UCLOGIC_RDESC_PEN_V2_ID;
	pen->inrange = UCLOGIC_PARAMS_PEN_INRANGE_NONE;
	pen->fragmented_hires = true;
	found = true;
finish:
	*pfound = found;
	rc = 0;
cleanup:
	kfree(desc_ptr);
	kfree(buf);
	return rc;
}