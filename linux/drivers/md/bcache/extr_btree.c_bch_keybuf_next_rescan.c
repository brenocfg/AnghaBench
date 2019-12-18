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
struct keybuf_key {int dummy; } ;
struct keybuf {int /*<<< orphan*/  last_scanned; } ;
struct cache_set {int dummy; } ;
struct bkey {int dummy; } ;
typedef  int /*<<< orphan*/  keybuf_pred_fn ;

/* Variables and functions */
 struct keybuf_key* bch_keybuf_next (struct keybuf*) ; 
 int /*<<< orphan*/  bch_refill_keybuf (struct cache_set*,struct keybuf*,struct bkey*,int /*<<< orphan*/ *) ; 
 scalar_t__ bkey_cmp (int /*<<< orphan*/ *,struct bkey*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

struct keybuf_key *bch_keybuf_next_rescan(struct cache_set *c,
					  struct keybuf *buf,
					  struct bkey *end,
					  keybuf_pred_fn *pred)
{
	struct keybuf_key *ret;

	while (1) {
		ret = bch_keybuf_next(buf);
		if (ret)
			break;

		if (bkey_cmp(&buf->last_scanned, end) >= 0) {
			pr_debug("scan finished");
			break;
		}

		bch_refill_keybuf(c, buf, end, pred);
	}

	return ret;
}