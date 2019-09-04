#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  map_lock; int /*<<< orphan*/  lock; struct platform_device* pdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 TYPE_1__* sm_state ; 
 int /*<<< orphan*/  vc_sm_connected_init ; 
 int /*<<< orphan*/  vchiq_add_connected_callback (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm2835_vcsm_probe(struct platform_device *pdev)
{
	pr_info("vc-sm: Videocore shared memory driver\n");

	sm_state = kzalloc(sizeof(*sm_state), GFP_KERNEL);
	if (!sm_state)
		return -ENOMEM;
	sm_state->pdev = pdev;
	mutex_init(&sm_state->lock);
	mutex_init(&sm_state->map_lock);

	vchiq_add_connected_callback(vc_sm_connected_init);
	return 0;
}