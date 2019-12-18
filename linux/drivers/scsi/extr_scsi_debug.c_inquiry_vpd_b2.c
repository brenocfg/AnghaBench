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

/* Variables and functions */
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ scsi_debug_lbp () ; 
 int sdebug_lbprz ; 
 scalar_t__ sdebug_lbpu ; 
 scalar_t__ sdebug_lbpws ; 
 scalar_t__ sdebug_lbpws10 ; 

__attribute__((used)) static int inquiry_vpd_b2(unsigned char *arr)
{
	memset(arr, 0, 0x4);
	arr[0] = 0;			/* threshold exponent */
	if (sdebug_lbpu)
		arr[1] = 1 << 7;
	if (sdebug_lbpws)
		arr[1] |= 1 << 6;
	if (sdebug_lbpws10)
		arr[1] |= 1 << 5;
	if (sdebug_lbprz && scsi_debug_lbp())
		arr[1] |= (sdebug_lbprz & 0x7) << 2;  /* sbc4r07 and later */
	/* anc_sup=0; dp=0 (no provisioning group descriptor) */
	/* minimum_percentage=0; provisioning_type=0 (unknown) */
	/* threshold_percentage=0 */
	return 0x4;
}