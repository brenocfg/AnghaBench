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
struct skd_request_context {int /*<<< orphan*/  state; } ;
struct skd_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SKD_REQ_STATE_IDLE ; 

__attribute__((used)) static void skd_release_skreq(struct skd_device *skdev,
			      struct skd_request_context *skreq)
{
	/*
	 * Reclaim the skd_request_context
	 */
	skreq->state = SKD_REQ_STATE_IDLE;
}