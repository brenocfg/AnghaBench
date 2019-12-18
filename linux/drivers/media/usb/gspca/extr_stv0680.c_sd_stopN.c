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
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  stv0680_handle_error (struct gspca_dev*,int /*<<< orphan*/ ) ; 
 int stv_sndctrl (struct gspca_dev*,int,int,int,int) ; 

__attribute__((used)) static void sd_stopN(struct gspca_dev *gspca_dev)
{
	/* This is a high priority command; it stops all lower order cmds */
	if (stv_sndctrl(gspca_dev, 1, 0x04, 0x0000, 0x0) != 0x0)
		stv0680_handle_error(gspca_dev, -EIO);
}