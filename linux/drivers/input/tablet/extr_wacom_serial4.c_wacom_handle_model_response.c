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
struct wacom {int* data; int res_x; int res_y; int extra_z_bits; int flags; int max_x; int max_y; int eraser_mask; TYPE_2__* dev; int /*<<< orphan*/  result; } ;
struct TYPE_3__ {int version; } ;
struct TYPE_4__ {char* name; int /*<<< orphan*/  dev; TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int F_COVERS_SCREEN ; 
 int F_HAS_SCROLLWHEEL ; 
 int F_HAS_STYLUS2 ; 
#define  MODEL_ARTPAD_II 133 
#define  MODEL_CINTIQ 132 
#define  MODEL_CINTIQ2 131 
#define  MODEL_DIGITIZER_II 130 
#define  MODEL_GRAPHIRE 129 
#define  MODEL_PENPARTNER 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char*,int,int) ; 
 int sscanf (char*,char*,int*,int*) ; 
 char* strrchr (int*,char) ; 

__attribute__((used)) static void wacom_handle_model_response(struct wacom *wacom)
{
	int major_v, minor_v, r = 0;
	char *p;

	p = strrchr(wacom->data, 'V');
	if (p)
		r = sscanf(p + 1, "%u.%u", &major_v, &minor_v);
	if (r != 2)
		major_v = minor_v = 0;

	switch (wacom->data[2] << 8 | wacom->data[3]) {
	case MODEL_CINTIQ:	/* UNTESTED */
	case MODEL_CINTIQ2:
		if ((wacom->data[2] << 8 | wacom->data[3]) == MODEL_CINTIQ) {
			wacom->dev->name = "Wacom Cintiq";
			wacom->dev->id.version = MODEL_CINTIQ;
		} else {
			wacom->dev->name = "Wacom Cintiq II";
			wacom->dev->id.version = MODEL_CINTIQ2;
		}
		wacom->res_x = 508;
		wacom->res_y = 508;

		switch (wacom->data[5] << 8 | wacom->data[6]) {
		case 0x3731: /* PL-710 */
			wacom->res_x = 2540;
			wacom->res_y = 2540;
			/* fall through */
		case 0x3535: /* PL-550 */
		case 0x3830: /* PL-800 */
			wacom->extra_z_bits = 2;
		}

		wacom->flags = F_COVERS_SCREEN;
		break;

	case MODEL_PENPARTNER:
		wacom->dev->name = "Wacom Penpartner";
		wacom->dev->id.version = MODEL_PENPARTNER;
		wacom->res_x = 1000;
		wacom->res_y = 1000;
		break;

	case MODEL_GRAPHIRE:
		wacom->dev->name = "Wacom Graphire";
		wacom->dev->id.version = MODEL_GRAPHIRE;
		wacom->res_x = 1016;
		wacom->res_y = 1016;
		wacom->max_x = 5103;
		wacom->max_y = 3711;
		wacom->extra_z_bits = 2;
		wacom->eraser_mask = 0x08;
		wacom->flags = F_HAS_STYLUS2 | F_HAS_SCROLLWHEEL;
		break;

	case MODEL_ARTPAD_II:
	case MODEL_DIGITIZER_II:
		wacom->dev->name = "Wacom Digitizer II";
		wacom->dev->id.version = MODEL_DIGITIZER_II;
		if (major_v == 1 && minor_v <= 2)
			wacom->extra_z_bits = 0; /* UNTESTED */
		break;

	default:
		dev_err(&wacom->dev->dev, "Unsupported Wacom model %s\n",
			wacom->data);
		wacom->result = -ENODEV;
		return;
	}

	dev_info(&wacom->dev->dev, "%s tablet, version %u.%u\n",
		 wacom->dev->name, major_v, minor_v);
}