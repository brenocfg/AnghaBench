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
struct nfp_net {int rx_coalesce_usecs; int rx_coalesce_max_frames; int tx_coalesce_usecs; int tx_coalesce_max_frames; } ;

/* Variables and functions */

__attribute__((used)) static void nfp_net_irqmod_init(struct nfp_net *nn)
{
	nn->rx_coalesce_usecs      = 50;
	nn->rx_coalesce_max_frames = 64;
	nn->tx_coalesce_usecs      = 50;
	nn->tx_coalesce_max_frames = 64;
}