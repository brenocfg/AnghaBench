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

/* Variables and functions */
 int /*<<< orphan*/  nvmet_bdev_ns_disable (struct nvmet_ns*) ; 
 int /*<<< orphan*/  nvmet_file_ns_disable (struct nvmet_ns*) ; 

__attribute__((used)) static void nvmet_ns_dev_disable(struct nvmet_ns *ns)
{
	nvmet_bdev_ns_disable(ns);
	nvmet_file_ns_disable(ns);
}