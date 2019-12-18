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
struct fb_var_screeninfo {int dummy; } ;
struct fb_info {int dummy; } ;
struct atafb_par {int dummy; } ;
struct TYPE_2__ {int (* decode_var ) (struct fb_var_screeninfo*,struct atafb_par*) ;int /*<<< orphan*/  (* encode_var ) (struct fb_var_screeninfo*,struct atafb_par*) ;} ;

/* Variables and functions */
 TYPE_1__* fbhw ; 
 int stub1 (struct fb_var_screeninfo*,struct atafb_par*) ; 
 int /*<<< orphan*/  stub2 (struct fb_var_screeninfo*,struct atafb_par*) ; 

__attribute__((used)) static int atafb_check_var(struct fb_var_screeninfo *var, struct fb_info *info)
{
	int err;
	struct atafb_par par;

	/* Validate wanted screen parameters */
	// if ((err = ata_decode_var(var, &par)))
	err = fbhw->decode_var(var, &par);
	if (err)
		return err;

	/* Encode (possibly rounded) screen parameters */
	fbhw->encode_var(var, &par);
	return 0;
}