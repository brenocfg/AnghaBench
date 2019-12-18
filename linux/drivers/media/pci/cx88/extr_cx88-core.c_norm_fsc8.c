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
typedef  int v4l2_std_id ;

/* Variables and functions */
 int V4L2_STD_NTSC ; 
 int V4L2_STD_PAL_M ; 
 int V4L2_STD_PAL_Nc ; 

__attribute__((used)) static inline unsigned int norm_fsc8(v4l2_std_id norm)
{
	if (norm & V4L2_STD_PAL_M)
		return 28604892;      // 3.575611 MHz

	if (norm & (V4L2_STD_PAL_Nc))
		return 28656448;      // 3.582056 MHz

	if (norm & V4L2_STD_NTSC) // All NTSC/M and variants
		return 28636360;      // 3.57954545 MHz +/- 10 Hz

	/*
	 * SECAM have also different sub carrier for chroma,
	 * but step_db and step_dr, at cx88_set_tvnorm already handles that.
	 *
	 * The same FSC applies to PAL/BGDKIH, PAL/60, NTSC/4.43 and PAL/N
	 */

	return 35468950;      // 4.43361875 MHz +/- 5 Hz
}