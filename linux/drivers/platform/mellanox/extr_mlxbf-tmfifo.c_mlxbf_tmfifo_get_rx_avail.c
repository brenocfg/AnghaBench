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
struct mlxbf_tmfifo {scalar_t__ rx_base; } ;

/* Variables and functions */
 int FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MLXBF_TMFIFO_RX_STS ; 
 int /*<<< orphan*/  MLXBF_TMFIFO_RX_STS__COUNT_MASK ; 
 int /*<<< orphan*/  readq (scalar_t__) ; 

__attribute__((used)) static int mlxbf_tmfifo_get_rx_avail(struct mlxbf_tmfifo *fifo)
{
	u64 sts;

	sts = readq(fifo->rx_base + MLXBF_TMFIFO_RX_STS);
	return FIELD_GET(MLXBF_TMFIFO_RX_STS__COUNT_MASK, sts);
}