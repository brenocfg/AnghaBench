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
typedef  int /*<<< orphan*/  u64 ;
struct chtls_hws {int /*<<< orphan*/  tx_seq_no; } ;

/* Variables and functions */

__attribute__((used)) static u64 tlstx_incr_seqnum(struct chtls_hws *hws)
{
	return hws->tx_seq_no++;
}