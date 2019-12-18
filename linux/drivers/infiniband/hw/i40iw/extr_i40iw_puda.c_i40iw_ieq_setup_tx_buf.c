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
struct i40iw_puda_buf {int /*<<< orphan*/  hdrlen; int /*<<< orphan*/  ipv4; int /*<<< orphan*/  tcphlen; int /*<<< orphan*/  maclen; } ;

/* Variables and functions */
 int /*<<< orphan*/  i40iw_ieq_copy_to_txbuf (struct i40iw_puda_buf*,struct i40iw_puda_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i40iw_ieq_setup_tx_buf(struct i40iw_puda_buf *buf,
				   struct i40iw_puda_buf *txbuf)
{
	txbuf->maclen = buf->maclen;
	txbuf->tcphlen = buf->tcphlen;
	txbuf->ipv4 = buf->ipv4;
	txbuf->hdrlen = buf->hdrlen;
	i40iw_ieq_copy_to_txbuf(buf, txbuf, 0, 0, buf->hdrlen);
}