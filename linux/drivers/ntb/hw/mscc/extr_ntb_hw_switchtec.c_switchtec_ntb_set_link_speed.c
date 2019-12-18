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
struct switchtec_ntb {void* link_width; void* link_speed; int /*<<< orphan*/  peer_partition; int /*<<< orphan*/  self_partition; int /*<<< orphan*/  link_is_up; } ;
typedef  enum ntb_width { ____Placeholder_ntb_width } ntb_width ;
typedef  enum ntb_speed { ____Placeholder_ntb_speed } ntb_speed ;

/* Variables and functions */
 void* NTB_SPEED_NONE ; 
 void* NTB_WIDTH_NONE ; 
 void* min (int,int) ; 
 int /*<<< orphan*/  switchtec_ntb_part_link_speed (struct switchtec_ntb*,int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static void switchtec_ntb_set_link_speed(struct switchtec_ntb *sndev)
{
	enum ntb_speed self_speed, peer_speed;
	enum ntb_width self_width, peer_width;

	if (!sndev->link_is_up) {
		sndev->link_speed = NTB_SPEED_NONE;
		sndev->link_width = NTB_WIDTH_NONE;
		return;
	}

	switchtec_ntb_part_link_speed(sndev, sndev->self_partition,
				      &self_speed, &self_width);
	switchtec_ntb_part_link_speed(sndev, sndev->peer_partition,
				      &peer_speed, &peer_width);

	sndev->link_speed = min(self_speed, peer_speed);
	sndev->link_width = min(self_width, peer_width);
}