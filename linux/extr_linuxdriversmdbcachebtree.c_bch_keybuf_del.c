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
struct keybuf {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __bch_keybuf_del (struct keybuf*,struct keybuf_key*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void bch_keybuf_del(struct keybuf *buf, struct keybuf_key *w)
{
	spin_lock(&buf->lock);
	__bch_keybuf_del(buf, w);
	spin_unlock(&buf->lock);
}