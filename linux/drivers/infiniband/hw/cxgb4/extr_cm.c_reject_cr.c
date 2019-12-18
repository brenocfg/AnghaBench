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
struct cpl_tid_release {int dummy; } ;
struct c4iw_dev {int /*<<< orphan*/  rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,struct c4iw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_tid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int) ; 

__attribute__((used)) static void reject_cr(struct c4iw_dev *dev, u32 hwtid, struct sk_buff *skb)
{
	pr_debug("c4iw_dev %p tid %u\n", dev, hwtid);
	skb_trim(skb, sizeof(struct cpl_tid_release));
	release_tid(&dev->rdev, hwtid, skb);
	return;
}