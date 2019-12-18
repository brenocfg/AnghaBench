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
 int /*<<< orphan*/  SE401_REQ_CAMERA_POWER ; 
 int /*<<< orphan*/  SE401_REQ_LED_CONTROL ; 
 int /*<<< orphan*/  SE401_REQ_STOP_CONTINUOUS_CAPTURE ; 
 int /*<<< orphan*/  se401_write_req (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sd_stopN(struct gspca_dev *gspca_dev)
{
	se401_write_req(gspca_dev, SE401_REQ_STOP_CONTINUOUS_CAPTURE, 0, 0);
	se401_write_req(gspca_dev, SE401_REQ_LED_CONTROL, 0, 0);
	se401_write_req(gspca_dev, SE401_REQ_CAMERA_POWER, 0, 0);
}