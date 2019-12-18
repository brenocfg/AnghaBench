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
struct rcar_du_device {int /*<<< orphan*/  dev; } ;
struct rcar_du_crtc {int /*<<< orphan*/  flip_wait; struct rcar_du_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  rcar_du_crtc_finish_page_flip (struct rcar_du_crtc*) ; 
 int /*<<< orphan*/  rcar_du_crtc_page_flip_pending (struct rcar_du_crtc*) ; 
 scalar_t__ wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rcar_du_crtc_wait_page_flip(struct rcar_du_crtc *rcrtc)
{
	struct rcar_du_device *rcdu = rcrtc->dev;

	if (wait_event_timeout(rcrtc->flip_wait,
			       !rcar_du_crtc_page_flip_pending(rcrtc),
			       msecs_to_jiffies(50)))
		return;

	dev_warn(rcdu->dev, "page flip timeout\n");

	rcar_du_crtc_finish_page_flip(rcrtc);
}