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
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  SE401_REQ_SET_BRT ; 
 int /*<<< orphan*/  se401_write_req (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setbrightness(struct gspca_dev *gspca_dev, s32 val)
{
	/* HDG: this does not seem to do anything on my cam */
	se401_write_req(gspca_dev, SE401_REQ_SET_BRT, val, 0);
}