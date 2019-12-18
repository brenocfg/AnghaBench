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
struct s3c_rtc {int ticnt_en_save; scalar_t__ base; int /*<<< orphan*/  ticnt_save; } ;

/* Variables and functions */
 scalar_t__ S3C2410_RTCCON ; 
 scalar_t__ S3C2410_TICNT ; 
 unsigned int readw (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  writew (unsigned int,scalar_t__) ; 

__attribute__((used)) static void s3c6410_rtc_restore_tick_cnt(struct s3c_rtc *info)
{
	unsigned int con;

	writel(info->ticnt_save, info->base + S3C2410_TICNT);
	if (info->ticnt_en_save) {
		con = readw(info->base + S3C2410_RTCCON);
		writew(con | info->ticnt_en_save, info->base + S3C2410_RTCCON);
	}
}