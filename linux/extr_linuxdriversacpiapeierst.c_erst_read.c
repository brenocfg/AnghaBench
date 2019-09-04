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
struct cper_record_header {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  __erst_read (int /*<<< orphan*/ ,struct cper_record_header*,size_t) ; 
 scalar_t__ erst_disable ; 
 int /*<<< orphan*/  erst_lock ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

ssize_t erst_read(u64 record_id, struct cper_record_header *record,
		  size_t buflen)
{
	ssize_t len;
	unsigned long flags;

	if (erst_disable)
		return -ENODEV;

	raw_spin_lock_irqsave(&erst_lock, flags);
	len = __erst_read(record_id, record, buflen);
	raw_spin_unlock_irqrestore(&erst_lock, flags);
	return len;
}