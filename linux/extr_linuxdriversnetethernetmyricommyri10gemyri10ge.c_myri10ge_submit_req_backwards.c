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
struct myri10ge_tx_buf {int req; int mask; int /*<<< orphan*/ * lanai; } ;
struct mcp_kreq_ether_send {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  myri10ge_pio_copy (int /*<<< orphan*/ *,struct mcp_kreq_ether_send*,int) ; 

__attribute__((used)) static inline void
myri10ge_submit_req_backwards(struct myri10ge_tx_buf *tx,
			      struct mcp_kreq_ether_send *src, int cnt)
{
	int idx, starting_slot;
	starting_slot = tx->req;
	while (cnt > 1) {
		cnt--;
		idx = (starting_slot + cnt) & tx->mask;
		myri10ge_pio_copy(&tx->lanai[idx], &src[cnt], sizeof(*src));
		mb();
	}
}