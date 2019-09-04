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
struct sd {scalar_t__ bridge; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ BRIDGE_OV511 ; 
 scalar_t__ BRIDGE_OV511PLUS ; 
 int /*<<< orphan*/  D_PROBE ; 
 int R51x_COMP_LUT_BEGIN ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  reg_w (struct sd*,int,unsigned char) ; 

__attribute__((used)) static void ov51x_upload_quan_tables(struct sd *sd)
{
	static const unsigned char yQuanTable511[] = {
		0, 1, 1, 2, 2, 3, 3, 4,
		1, 1, 1, 2, 2, 3, 4, 4,
		1, 1, 2, 2, 3, 4, 4, 4,
		2, 2, 2, 3, 4, 4, 4, 4,
		2, 2, 3, 4, 4, 5, 5, 5,
		3, 3, 4, 4, 5, 5, 5, 5,
		3, 4, 4, 4, 5, 5, 5, 5,
		4, 4, 4, 4, 5, 5, 5, 5
	};

	static const unsigned char uvQuanTable511[] = {
		0, 2, 2, 3, 4, 4, 4, 4,
		2, 2, 2, 4, 4, 4, 4, 4,
		2, 2, 3, 4, 4, 4, 4, 4,
		3, 4, 4, 4, 4, 4, 4, 4,
		4, 4, 4, 4, 4, 4, 4, 4,
		4, 4, 4, 4, 4, 4, 4, 4,
		4, 4, 4, 4, 4, 4, 4, 4,
		4, 4, 4, 4, 4, 4, 4, 4
	};

	/* OV518 quantization tables are 8x4 (instead of 8x8) */
	static const unsigned char yQuanTable518[] = {
		5, 4, 5, 6, 6, 7, 7, 7,
		5, 5, 5, 5, 6, 7, 7, 7,
		6, 6, 6, 6, 7, 7, 7, 8,
		7, 7, 6, 7, 7, 7, 8, 8
	};
	static const unsigned char uvQuanTable518[] = {
		6, 6, 6, 7, 7, 7, 7, 7,
		6, 6, 6, 7, 7, 7, 7, 7,
		6, 6, 6, 7, 7, 7, 7, 8,
		7, 7, 7, 7, 7, 7, 8, 8
	};

	struct gspca_dev *gspca_dev = (struct gspca_dev *)sd;
	const unsigned char *pYTable, *pUVTable;
	unsigned char val0, val1;
	int i, size, reg = R51x_COMP_LUT_BEGIN;

	gspca_dbg(gspca_dev, D_PROBE, "Uploading quantization tables\n");

	if (sd->bridge == BRIDGE_OV511 || sd->bridge == BRIDGE_OV511PLUS) {
		pYTable = yQuanTable511;
		pUVTable = uvQuanTable511;
		size = 32;
	} else {
		pYTable = yQuanTable518;
		pUVTable = uvQuanTable518;
		size = 16;
	}

	for (i = 0; i < size; i++) {
		val0 = *pYTable++;
		val1 = *pYTable++;
		val0 &= 0x0f;
		val1 &= 0x0f;
		val0 |= val1 << 4;
		reg_w(sd, reg, val0);

		val0 = *pUVTable++;
		val1 = *pUVTable++;
		val0 &= 0x0f;
		val1 &= 0x0f;
		val0 |= val1 << 4;
		reg_w(sd, reg + size, val0);

		reg++;
	}
}