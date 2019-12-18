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
struct s3c_rtc {scalar_t__ base; int /*<<< orphan*/  ticnt_save; int /*<<< orphan*/  ticnt_en_save; } ;

/* Variables and functions */
 scalar_t__ S3C2410_RTCCON ; 
 scalar_t__ S3C2410_TICNT ; 
 int /*<<< orphan*/  S3C64XX_RTCCON_TICEN ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  readw (scalar_t__) ; 

__attribute__((used)) static void s3c6410_rtc_save_tick_cnt(struct s3c_rtc *info)
{
	info->ticnt_en_save = readw(info->base + S3C2410_RTCCON);
	info->ticnt_en_save &= S3C64XX_RTCCON_TICEN;
	info->ticnt_save = readl(info->base + S3C2410_TICNT);
}