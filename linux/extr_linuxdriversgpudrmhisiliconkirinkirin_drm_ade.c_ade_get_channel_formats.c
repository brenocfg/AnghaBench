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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
#define  ADE_CH1 128 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/ * channel_formats1 ; 

u32 ade_get_channel_formats(u8 ch, const u32 **formats)
{
	switch (ch) {
	case ADE_CH1:
		*formats = channel_formats1;
		return ARRAY_SIZE(channel_formats1);
	default:
		DRM_ERROR("no this channel %d\n", ch);
		*formats = NULL;
		return 0;
	}
}