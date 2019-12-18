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
struct wacom_features {scalar_t__ type; int device_type; } ;
struct wacom_wac {struct wacom_features features; } ;

/* Variables and functions */
 scalar_t__ INTUOSHT2 ; 
 int WACOM_DEVICETYPE_PEN ; 
 size_t WACOM_PKGLEN_BBFUN ; 
 size_t WACOM_PKGLEN_BBPEN ; 
 size_t WACOM_PKGLEN_BBTOUCH ; 
 size_t WACOM_PKGLEN_BBTOUCH3 ; 
 int wacom_bpt3_touch (struct wacom_wac*) ; 
 int wacom_bpt_pen (struct wacom_wac*) ; 
 int wacom_bpt_touch (struct wacom_wac*) ; 
 int wacom_intuos_irq (struct wacom_wac*) ; 

__attribute__((used)) static int wacom_bpt_irq(struct wacom_wac *wacom, size_t len)
{
	struct wacom_features *features = &wacom->features;

	if ((features->type == INTUOSHT2) &&
	    (features->device_type & WACOM_DEVICETYPE_PEN))
		return wacom_intuos_irq(wacom);
	else if (len == WACOM_PKGLEN_BBTOUCH)
		return wacom_bpt_touch(wacom);
	else if (len == WACOM_PKGLEN_BBTOUCH3)
		return wacom_bpt3_touch(wacom);
	else if (len == WACOM_PKGLEN_BBFUN || len == WACOM_PKGLEN_BBPEN)
		return wacom_bpt_pen(wacom);

	return 0;
}