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
struct vmw_screen_object_unit {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct vmw_screen_object_unit*) ; 
 int /*<<< orphan*/  vmw_du_cleanup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vmw_sou_destroy(struct vmw_screen_object_unit *sou)
{
	vmw_du_cleanup(&sou->base);
	kfree(sou);
}