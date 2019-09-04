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
struct sti_dvo {int /*<<< orphan*/  bridge; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct sti_dvo* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  drm_bridge_remove (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sti_dvo_unbind(struct device *dev,
			   struct device *master, void *data)
{
	struct sti_dvo *dvo = dev_get_drvdata(dev);

	drm_bridge_remove(dvo->bridge);
}