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
struct sk_buff {int dummy; } ;
struct c4iw_wr_wait {int dummy; } ;
struct c4iw_rdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  c4iw_get_wr_wait (struct c4iw_wr_wait*) ; 
 int c4iw_ofld_send (struct c4iw_rdev*,struct sk_buff*) ; 
 int /*<<< orphan*/  c4iw_put_wr_wait (struct c4iw_wr_wait*) ; 
 int c4iw_wait_for_reply (struct c4iw_rdev*,struct c4iw_wr_wait*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  pr_debug (char*,char const*,struct c4iw_wr_wait*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int c4iw_ref_send_wait(struct c4iw_rdev *rdev,
				     struct sk_buff *skb,
				     struct c4iw_wr_wait *wr_waitp,
				     u32 hwtid, u32 qpid,
				     const char *func)
{
	int ret;

	pr_debug("%s wr_wait %p hwtid %u qpid %u\n", func, wr_waitp, hwtid,
		 qpid);
	c4iw_get_wr_wait(wr_waitp);
	ret = c4iw_ofld_send(rdev, skb);
	if (ret) {
		c4iw_put_wr_wait(wr_waitp);
		return ret;
	}
	return c4iw_wait_for_reply(rdev, wr_waitp, hwtid, qpid, func);
}