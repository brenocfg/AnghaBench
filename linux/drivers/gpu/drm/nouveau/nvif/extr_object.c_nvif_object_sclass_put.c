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
struct nvif_sclass {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nvif_sclass*) ; 

void
nvif_object_sclass_put(struct nvif_sclass **psclass)
{
	kfree(*psclass);
	*psclass = NULL;
}