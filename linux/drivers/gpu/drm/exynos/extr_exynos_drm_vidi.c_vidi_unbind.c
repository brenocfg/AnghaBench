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
struct vidi_context {int /*<<< orphan*/  timer; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 struct vidi_context* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static void vidi_unbind(struct device *dev, struct device *master, void *data)
{
	struct vidi_context *ctx = dev_get_drvdata(dev);

	del_timer_sync(&ctx->timer);
}