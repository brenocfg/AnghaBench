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
typedef  int /*<<< orphan*/  u16 ;
struct t4_swsqe {int dummy; } ;
struct t4_sq {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 scalar_t__ fill_swsqe (struct sk_buff*,struct t4_sq*,int /*<<< orphan*/ ,struct t4_swsqe*) ; 

__attribute__((used)) static int fill_swsqes(struct sk_buff *msg, struct t4_sq *sq,
		       u16 first_idx, struct t4_swsqe *first_sqe,
		       u16 last_idx, struct t4_swsqe *last_sqe)
{
	if (!first_sqe)
		goto out;
	if (fill_swsqe(msg, sq, first_idx, first_sqe))
		goto err;
	if (!last_sqe)
		goto out;
	if (fill_swsqe(msg, sq, last_idx, last_sqe))
		goto err;
out:
	return 0;
err:
	return -EMSGSIZE;
}