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
struct tty_struct {int dummy; } ;
struct n_hdlc_buf {int dummy; } ;
struct n_hdlc {int /*<<< orphan*/  rx_free_buf_list; int /*<<< orphan*/  rx_buf_list; } ;

/* Variables and functions */
 struct n_hdlc_buf* n_hdlc_buf_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  n_hdlc_buf_put (int /*<<< orphan*/ *,struct n_hdlc_buf*) ; 
 struct n_hdlc* tty2n_hdlc (struct tty_struct*) ; 

__attribute__((used)) static void flush_rx_queue(struct tty_struct *tty)
{
	struct n_hdlc *n_hdlc = tty2n_hdlc(tty);
	struct n_hdlc_buf *buf;

	while ((buf = n_hdlc_buf_get(&n_hdlc->rx_buf_list)))
		n_hdlc_buf_put(&n_hdlc->rx_free_buf_list, buf);
}