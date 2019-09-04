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
struct fdp1_fmt {int fmt; } ;

/* Variables and functions */

__attribute__((used)) static int fdp1_fmt_is_rgb(const struct fdp1_fmt *fmt)
{
	return fmt->fmt <= 0x1b; /* Last RGB code */
}