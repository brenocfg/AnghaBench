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
struct isp_prev_device {int /*<<< orphan*/  wait; } ;
struct isp_device {struct isp_prev_device isp_prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int preview_init_entities (struct isp_prev_device*) ; 
 int /*<<< orphan*/  preview_init_params (struct isp_prev_device*) ; 

int omap3isp_preview_init(struct isp_device *isp)
{
	struct isp_prev_device *prev = &isp->isp_prev;

	init_waitqueue_head(&prev->wait);

	preview_init_params(prev);

	return preview_init_entities(prev);
}