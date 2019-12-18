#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  v4l2_std_id ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  field; } ;
struct ipu_csi {TYPE_1__* ipu; } ;
typedef  enum v4l2_field { ____Placeholder_v4l2_field } v4l2_field ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSI_CCIR_CODE_1 ; 
 int /*<<< orphan*/  CSI_CCIR_CODE_2 ; 
 int /*<<< orphan*/  CSI_CCIR_CODE_3 ; 
 int CSI_CCIR_ERR_DET_EN ; 
 scalar_t__ V4L2_FIELD_IS_SEQUENTIAL (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int ipu_csi_translate_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_csi_write (struct ipu_csi*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ipu_csi_set_bt_interlaced_codes(struct ipu_csi *csi,
				const struct v4l2_mbus_framefmt *infmt,
				const struct v4l2_mbus_framefmt *outfmt,
				v4l2_std_id std)
{
	enum v4l2_field infield, outfield;
	bool swap_fields;

	/* get translated field type of input and output */
	infield = ipu_csi_translate_field(infmt->field, std);
	outfield = ipu_csi_translate_field(outfmt->field, std);

	/*
	 * Write the H-V-F codes the CSI will match against the
	 * incoming data for start/end of active and blanking
	 * field intervals. If input and output field types are
	 * sequential but not the same (one is SEQ_BT and the other
	 * is SEQ_TB), swap the F-bit so that the CSI will capture
	 * field 1 lines before field 0 lines.
	 */
	swap_fields = (V4L2_FIELD_IS_SEQUENTIAL(infield) &&
		       V4L2_FIELD_IS_SEQUENTIAL(outfield) &&
		       infield != outfield);

	if (!swap_fields) {
		/*
		 * Field0BlankEnd  = 110, Field0BlankStart  = 010
		 * Field0ActiveEnd = 100, Field0ActiveStart = 000
		 * Field1BlankEnd  = 111, Field1BlankStart  = 011
		 * Field1ActiveEnd = 101, Field1ActiveStart = 001
		 */
		ipu_csi_write(csi, 0x40596 | CSI_CCIR_ERR_DET_EN,
			      CSI_CCIR_CODE_1);
		ipu_csi_write(csi, 0xD07DF, CSI_CCIR_CODE_2);
	} else {
		dev_dbg(csi->ipu->dev, "capture field swap\n");

		/* same as above but with F-bit inverted */
		ipu_csi_write(csi, 0xD07DF | CSI_CCIR_ERR_DET_EN,
			      CSI_CCIR_CODE_1);
		ipu_csi_write(csi, 0x40596, CSI_CCIR_CODE_2);
	}

	ipu_csi_write(csi, 0xFF0000, CSI_CCIR_CODE_3);

	return 0;
}