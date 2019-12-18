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
struct v4l2_fract {int numerator; int denominator; } ;
struct tw5864_input {int std; struct tw5864_dev* root; } ;
struct tw5864_dev {TYPE_1__* pci; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
#define  STD_NTSC 130 
#define  STD_PAL 129 
#define  STD_SECAM 128 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int tw5864_frameinterval_get(struct tw5864_input *input,
				    struct v4l2_fract *frameinterval)
{
	struct tw5864_dev *dev = input->root;

	switch (input->std) {
	case STD_NTSC:
		frameinterval->numerator = 1001;
		frameinterval->denominator = 30000;
		break;
	case STD_PAL:
	case STD_SECAM:
		frameinterval->numerator = 1;
		frameinterval->denominator = 25;
		break;
	default:
		dev_warn(&dev->pci->dev, "tw5864_frameinterval_get requested for unknown std %d\n",
			 input->std);
		return -EINVAL;
	}

	return 0;
}