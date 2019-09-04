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

__attribute__((used)) static inline unsigned int VENUS_EXTRADATA_SIZE(int width, int height)
{
	(void)height;
	(void)width;

	/*
	 * In the future, calculate the size based on the w/h but just
	 * hardcode it for now since 16K satisfies all current usecases.
	 */
	return 16 * 1024;
}