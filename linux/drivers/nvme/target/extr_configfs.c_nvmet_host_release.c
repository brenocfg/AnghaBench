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
struct nvmet_host {int dummy; } ;
struct config_item {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nvmet_host*) ; 
 struct nvmet_host* to_host (struct config_item*) ; 

__attribute__((used)) static void nvmet_host_release(struct config_item *item)
{
	struct nvmet_host *host = to_host(item);

	kfree(host);
}