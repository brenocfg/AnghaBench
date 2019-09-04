#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int Command; } ;
typedef  TYPE_1__ capi_msg ;

/* Variables and functions */
#define  CAPI_FACILITY 128 
 int isdn_tty_capi_facility (TYPE_1__*) ; 

__attribute__((used)) static int
isdn_capi_rec_hl_msg(capi_msg *cm)
{
	switch (cm->Command) {
	case CAPI_FACILITY:
		/* in the moment only handled in tty */
		return (isdn_tty_capi_facility(cm));
	default:
		return (-1);
	}
}