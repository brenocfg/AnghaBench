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
typedef  scalar_t__ u64 ;
struct repaper_epd {int factored_stage_time; } ;
typedef  enum repaper_stage { ____Placeholder_repaper_stage } repaper_stage ;

/* Variables and functions */
 scalar_t__ local_clock () ; 
 int /*<<< orphan*/  repaper_frame_data (struct repaper_epd*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void repaper_frame_data_repeat(struct repaper_epd *epd, const u8 *image,
				      const u8 *mask, enum repaper_stage stage)
{
	u64 start = local_clock();
	u64 end = start + (epd->factored_stage_time * 1000 * 1000);

	do {
		repaper_frame_data(epd, image, mask, stage);
	} while (local_clock() < end);
}