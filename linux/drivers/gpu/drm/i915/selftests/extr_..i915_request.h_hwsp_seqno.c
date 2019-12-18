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
typedef  int /*<<< orphan*/  u32 ;
struct i915_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __hwsp_seqno (struct i915_request const*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static inline u32 hwsp_seqno(const struct i915_request *rq)
{
	u32 seqno;

	rcu_read_lock(); /* the HWSP may be freed at runtime */
	seqno = __hwsp_seqno(rq);
	rcu_read_unlock();

	return seqno;
}