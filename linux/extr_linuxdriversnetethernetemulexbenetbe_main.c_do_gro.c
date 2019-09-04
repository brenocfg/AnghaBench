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
struct be_rx_compl_info {scalar_t__ l4_csum; int /*<<< orphan*/  err; scalar_t__ tcpf; } ;

/* Variables and functions */

__attribute__((used)) static inline bool do_gro(struct be_rx_compl_info *rxcp)
{
	return (rxcp->tcpf && !rxcp->err && rxcp->l4_csum) ? true : false;
}