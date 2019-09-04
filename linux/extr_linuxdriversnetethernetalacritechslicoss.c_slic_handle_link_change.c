#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  link_paddr; } ;
struct slic_device {TYPE_1__ shmem; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLIC_UPR_LSTAT ; 
 int slic_new_upr (struct slic_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int slic_handle_link_change(struct slic_device *sdev)
{
	return slic_new_upr(sdev, SLIC_UPR_LSTAT, sdev->shmem.link_paddr);
}