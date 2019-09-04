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
struct vsp1_rwpf {int /*<<< orphan*/  dlm; } ;
struct vsp1_entity {int dummy; } ;

/* Variables and functions */
 struct vsp1_rwpf* entity_to_rwpf (struct vsp1_entity*) ; 
 int /*<<< orphan*/  vsp1_dlm_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vsp1_wpf_destroy(struct vsp1_entity *entity)
{
	struct vsp1_rwpf *wpf = entity_to_rwpf(entity);

	vsp1_dlm_destroy(wpf->dlm);
}