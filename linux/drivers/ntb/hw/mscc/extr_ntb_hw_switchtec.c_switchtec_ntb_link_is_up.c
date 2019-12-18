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
typedef  int /*<<< orphan*/  u64 ;
struct switchtec_ntb {int link_speed; int link_width; int /*<<< orphan*/  link_is_up; } ;
struct ntb_dev {int dummy; } ;
typedef  enum ntb_width { ____Placeholder_ntb_width } ntb_width ;
typedef  enum ntb_speed { ____Placeholder_ntb_speed } ntb_speed ;

/* Variables and functions */
 struct switchtec_ntb* ntb_sndev (struct ntb_dev*) ; 

__attribute__((used)) static u64 switchtec_ntb_link_is_up(struct ntb_dev *ntb,
				    enum ntb_speed *speed,
				    enum ntb_width *width)
{
	struct switchtec_ntb *sndev = ntb_sndev(ntb);

	if (speed)
		*speed = sndev->link_speed;
	if (width)
		*width = sndev->link_width;

	return sndev->link_is_up;
}