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
typedef  int /*<<< orphan*/  u8 ;
struct repaper_epd {unsigned int height; } ;
typedef  enum repaper_stage { ____Placeholder_repaper_stage } repaper_stage ;

/* Variables and functions */
 int /*<<< orphan*/  repaper_one_line (struct repaper_epd*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void repaper_frame_fixed(struct repaper_epd *epd, u8 fixed_value,
				enum repaper_stage stage)
{
	unsigned int line;

	for (line = 0; line < epd->height; line++)
		repaper_one_line(epd, line, NULL, fixed_value, NULL, stage);
}