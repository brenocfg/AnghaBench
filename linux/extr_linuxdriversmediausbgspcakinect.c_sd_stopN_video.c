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
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  write_register (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void sd_stopN_video(struct gspca_dev *gspca_dev)
{
	/* reset video stream */
	write_register(gspca_dev, 0x05, 0x00);
}