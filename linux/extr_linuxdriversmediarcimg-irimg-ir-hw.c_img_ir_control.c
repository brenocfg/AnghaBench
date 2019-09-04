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
typedef  int u32 ;
struct img_ir_control {int code_type; scalar_t__ bitinvd2; scalar_t__ bitoriend2; scalar_t__ decodend2; scalar_t__ bitinv; scalar_t__ d1validsel; scalar_t__ bitorien; scalar_t__ decodinpol; scalar_t__ ldrdec; scalar_t__ hdrtog; scalar_t__ decoden; } ;

/* Variables and functions */
 int IMG_IR_BITINV ; 
 int IMG_IR_BITINVD2 ; 
 int IMG_IR_BITORIEN ; 
 int IMG_IR_BITORIEND2 ; 
 int IMG_IR_CODETYPE_SHIFT ; 
 int IMG_IR_D1VALIDSEL ; 
 int IMG_IR_DECODEN ; 
 int IMG_IR_DECODEND2 ; 
 int IMG_IR_DECODINPOL ; 
 int IMG_IR_HDRTOG ; 
 int IMG_IR_LDRDEC ; 

__attribute__((used)) static u32 img_ir_control(const struct img_ir_control *control)
{
	u32 ctrl = control->code_type << IMG_IR_CODETYPE_SHIFT;
	if (control->decoden)
		ctrl |= IMG_IR_DECODEN;
	if (control->hdrtog)
		ctrl |= IMG_IR_HDRTOG;
	if (control->ldrdec)
		ctrl |= IMG_IR_LDRDEC;
	if (control->decodinpol)
		ctrl |= IMG_IR_DECODINPOL;
	if (control->bitorien)
		ctrl |= IMG_IR_BITORIEN;
	if (control->d1validsel)
		ctrl |= IMG_IR_D1VALIDSEL;
	if (control->bitinv)
		ctrl |= IMG_IR_BITINV;
	if (control->decodend2)
		ctrl |= IMG_IR_DECODEND2;
	if (control->bitoriend2)
		ctrl |= IMG_IR_BITORIEND2;
	if (control->bitinvd2)
		ctrl |= IMG_IR_BITINVD2;
	return ctrl;
}