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
struct nvmet_ns {int dummy; } ;
struct config_item {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvmet_ns_free (struct nvmet_ns*) ; 
 struct nvmet_ns* to_nvmet_ns (struct config_item*) ; 

__attribute__((used)) static void nvmet_ns_release(struct config_item *item)
{
	struct nvmet_ns *ns = to_nvmet_ns(item);

	nvmet_ns_free(ns);
}