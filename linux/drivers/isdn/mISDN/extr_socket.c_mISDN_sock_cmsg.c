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
typedef  int /*<<< orphan*/  tv ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct msghdr {int dummy; } ;
struct __kernel_old_timeval {int dummy; } ;
struct TYPE_2__ {int cmask; } ;

/* Variables and functions */
 int MISDN_TIME_STAMP ; 
 int /*<<< orphan*/  SOL_MISDN ; 
 TYPE_1__* _pms (struct sock*) ; 
 int /*<<< orphan*/  put_cmsg (struct msghdr*,int /*<<< orphan*/ ,int,int,struct __kernel_old_timeval*) ; 
 int /*<<< orphan*/  skb_get_timestamp (struct sk_buff*,struct __kernel_old_timeval*) ; 

__attribute__((used)) static inline void
mISDN_sock_cmsg(struct sock *sk, struct msghdr *msg, struct sk_buff *skb)
{
	struct __kernel_old_timeval	tv;

	if (_pms(sk)->cmask & MISDN_TIME_STAMP) {
		skb_get_timestamp(skb, &tv);
		put_cmsg(msg, SOL_MISDN, MISDN_TIME_STAMP, sizeof(tv), &tv);
	}
}