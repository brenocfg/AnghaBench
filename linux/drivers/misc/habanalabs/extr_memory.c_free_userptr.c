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
struct hl_userptr {int dummy; } ;
struct hl_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hl_unpin_host_memory (struct hl_device*,struct hl_userptr*) ; 
 int /*<<< orphan*/  kfree (struct hl_userptr*) ; 

__attribute__((used)) static void free_userptr(struct hl_device *hdev, struct hl_userptr *userptr)
{
	hl_unpin_host_memory(hdev, userptr);
	kfree(userptr);
}