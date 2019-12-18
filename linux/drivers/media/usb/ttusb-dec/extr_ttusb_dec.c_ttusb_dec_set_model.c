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
struct ttusb_dec {int model; char* model_name; char* firmware_name; } ;
typedef  enum ttusb_dec_model { ____Placeholder_ttusb_dec_model } ttusb_dec_model ;

/* Variables and functions */
#define  TTUSB_DEC2000T 130 
#define  TTUSB_DEC2540T 129 
#define  TTUSB_DEC3000S 128 

__attribute__((used)) static void ttusb_dec_set_model(struct ttusb_dec *dec,
				enum ttusb_dec_model model)
{
	dec->model = model;

	switch (model) {
	case TTUSB_DEC2000T:
		dec->model_name = "DEC2000-t";
		dec->firmware_name = "dvb-ttusb-dec-2000t.fw";
		break;

	case TTUSB_DEC2540T:
		dec->model_name = "DEC2540-t";
		dec->firmware_name = "dvb-ttusb-dec-2540t.fw";
		break;

	case TTUSB_DEC3000S:
		dec->model_name = "DEC3000-s";
		dec->firmware_name = "dvb-ttusb-dec-3000s.fw";
		break;
	}
}