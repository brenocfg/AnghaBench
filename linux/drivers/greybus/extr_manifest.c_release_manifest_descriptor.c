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
struct manifest_desc {int /*<<< orphan*/  links; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct manifest_desc*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void release_manifest_descriptor(struct manifest_desc *descriptor)
{
	list_del(&descriptor->links);
	kfree(descriptor);
}