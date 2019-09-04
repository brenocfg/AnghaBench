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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ MEDIA_BUS_FMT_JPEG_1X8 ; 
 scalar_t__ MEDIA_BUS_FMT_S5C_UYVY_JPEG_1X8 ; 

__attribute__((used)) static inline bool fimc_user_defined_mbus_fmt(u32 code)
{
	return (code == MEDIA_BUS_FMT_JPEG_1X8 ||
		code == MEDIA_BUS_FMT_S5C_UYVY_JPEG_1X8);
}