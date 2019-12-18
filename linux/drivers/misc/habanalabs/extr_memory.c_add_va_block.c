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
typedef  int /*<<< orphan*/  u64 ;
struct hl_va_range {int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;
struct hl_device {int dummy; } ;

/* Variables and functions */
 int add_va_block_locked (struct hl_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int add_va_block(struct hl_device *hdev,
		struct hl_va_range *va_range, u64 start, u64 end)
{
	int rc;

	mutex_lock(&va_range->lock);
	rc = add_va_block_locked(hdev, &va_range->list, start, end);
	mutex_unlock(&va_range->lock);

	return rc;
}