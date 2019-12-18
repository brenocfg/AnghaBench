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
struct kpc_dma_device {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  kpc_dma_list ; 
 int /*<<< orphan*/  kpc_dma_mtx ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kpc_dma_add_device(struct kpc_dma_device *ldev)
{
	mutex_lock(&kpc_dma_mtx);
	list_add(&ldev->list, &kpc_dma_list);
	mutex_unlock(&kpc_dma_mtx);
}