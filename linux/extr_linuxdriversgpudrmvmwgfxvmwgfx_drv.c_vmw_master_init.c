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
struct vmw_master {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ttm_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vmw_master_init(struct vmw_master *vmaster)
{
	ttm_lock_init(&vmaster->lock);
}