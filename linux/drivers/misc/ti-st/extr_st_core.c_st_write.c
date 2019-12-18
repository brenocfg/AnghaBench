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
struct st_data_s {int /*<<< orphan*/ * tty; } ;
struct sk_buff {long len; } ;

/* Variables and functions */
 long EINVAL ; 
 int /*<<< orphan*/  pr_debug (char*,long) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  st_int_enqueue (struct st_data_s*,struct sk_buff*) ; 
 int /*<<< orphan*/  st_kim_ref (struct st_data_s**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st_tx_wakeup (struct st_data_s*) ; 
 scalar_t__ unlikely (int) ; 

long st_write(struct sk_buff *skb)
{
	struct st_data_s *st_gdata;
	long len;

	st_kim_ref(&st_gdata, 0);
	if (unlikely(skb == NULL || st_gdata == NULL
		|| st_gdata->tty == NULL)) {
		pr_err("data/tty unavailable to perform write");
		return -EINVAL;
	}

	pr_debug("%d to be written", skb->len);
	len = skb->len;

	/* st_ll to decide where to enqueue the skb */
	st_int_enqueue(st_gdata, skb);
	/* wake up */
	st_tx_wakeup(st_gdata);

	/* return number of bytes written */
	return len;
}