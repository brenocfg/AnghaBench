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
struct em28xx {scalar_t__ chip_id; scalar_t__ is_webcam; } ;

/* Variables and functions */
 scalar_t__ CHIP_ID_EM2860 ; 
 scalar_t__ CHIP_ID_EM2883 ; 
 int disable_vbi ; 

__attribute__((used)) static int em28xx_vbi_supported(struct em28xx *dev)
{
	/* Modprobe option to manually disable */
	if (disable_vbi == 1)
		return 0;

	if (dev->is_webcam)
		return 0;

	/* FIXME: check subdevices for VBI support */

	if (dev->chip_id == CHIP_ID_EM2860 ||
	    dev->chip_id == CHIP_ID_EM2883)
		return 1;

	/* Version of em28xx that does not support VBI */
	return 0;
}