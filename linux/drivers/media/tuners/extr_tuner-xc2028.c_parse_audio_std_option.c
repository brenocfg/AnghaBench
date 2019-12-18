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
typedef  int /*<<< orphan*/  v4l2_std_id ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_STD_A2 ; 
 int /*<<< orphan*/  V4L2_STD_A2_A ; 
 int /*<<< orphan*/  V4L2_STD_A2_B ; 
 int /*<<< orphan*/  V4L2_STD_NICAM ; 
 int /*<<< orphan*/  V4L2_STD_NICAM_A ; 
 int /*<<< orphan*/  V4L2_STD_NICAM_B ; 
 int /*<<< orphan*/  audio_std ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static  v4l2_std_id parse_audio_std_option(void)
{
	if (strcasecmp(audio_std, "A2") == 0)
		return V4L2_STD_A2;
	if (strcasecmp(audio_std, "A2/A") == 0)
		return V4L2_STD_A2_A;
	if (strcasecmp(audio_std, "A2/B") == 0)
		return V4L2_STD_A2_B;
	if (strcasecmp(audio_std, "NICAM") == 0)
		return V4L2_STD_NICAM;
	if (strcasecmp(audio_std, "NICAM/A") == 0)
		return V4L2_STD_NICAM_A;
	if (strcasecmp(audio_std, "NICAM/B") == 0)
		return V4L2_STD_NICAM_B;

	return 0;
}