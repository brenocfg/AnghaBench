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
#define  ADE_ABGR_8888 131 
#define  ADE_ARGB_8888 130 
#define  ADE_BGRA_8888 129 
#define  ADE_RGBA_8888 128 

__attribute__((used)) static bool has_Alpha_channel(int format)
{
	switch (format) {
	case ADE_ARGB_8888:
	case ADE_ABGR_8888:
	case ADE_RGBA_8888:
	case ADE_BGRA_8888:
		return true;
	default:
		return false;
	}
}