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
struct thc63_dev {int /*<<< orphan*/  next; } ;
struct drm_bridge {int /*<<< orphan*/  encoder; } ;

/* Variables and functions */
 int drm_bridge_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_bridge*) ; 
 struct thc63_dev* to_thc63 (struct drm_bridge*) ; 

__attribute__((used)) static int thc63_attach(struct drm_bridge *bridge)
{
	struct thc63_dev *thc63 = to_thc63(bridge);

	return drm_bridge_attach(bridge->encoder, thc63->next, bridge);
}