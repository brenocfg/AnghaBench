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
struct ad714x_chip {int product; unsigned short version; int /*<<< orphan*/  dev; int /*<<< orphan*/  (* read ) (struct ad714x_chip*,int /*<<< orphan*/ ,unsigned short*,int) ;} ;

/* Variables and functions */
#define  AD7142_PARTID 131 
#define  AD7143_PARTID 130 
#define  AD7147_PARTID 129 
#define  AD7148_PARTID 128 
 int /*<<< orphan*/  AD714X_PARTID_REG ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned short) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,unsigned short) ; 
 int /*<<< orphan*/  stub1 (struct ad714x_chip*,int /*<<< orphan*/ ,unsigned short*,int) ; 

__attribute__((used)) static int ad714x_hw_detect(struct ad714x_chip *ad714x)
{
	unsigned short data;

	ad714x->read(ad714x, AD714X_PARTID_REG, &data, 1);
	switch (data & 0xFFF0) {
	case AD7142_PARTID:
		ad714x->product = 0x7142;
		ad714x->version = data & 0xF;
		dev_info(ad714x->dev, "found AD7142 captouch, rev:%d\n",
				ad714x->version);
		return 0;

	case AD7143_PARTID:
		ad714x->product = 0x7143;
		ad714x->version = data & 0xF;
		dev_info(ad714x->dev, "found AD7143 captouch, rev:%d\n",
				ad714x->version);
		return 0;

	case AD7147_PARTID:
		ad714x->product = 0x7147;
		ad714x->version = data & 0xF;
		dev_info(ad714x->dev, "found AD7147(A) captouch, rev:%d\n",
				ad714x->version);
		return 0;

	case AD7148_PARTID:
		ad714x->product = 0x7148;
		ad714x->version = data & 0xF;
		dev_info(ad714x->dev, "found AD7148 captouch, rev:%d\n",
				ad714x->version);
		return 0;

	default:
		dev_err(ad714x->dev,
			"fail to detect AD714X captouch, read ID is %04x\n",
			data);
		return -ENODEV;
	}
}