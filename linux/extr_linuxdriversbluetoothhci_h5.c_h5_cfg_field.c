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
typedef  int u8 ;
struct h5 {int tx_win; } ;

/* Variables and functions */

__attribute__((used)) static u8 h5_cfg_field(struct h5 *h5)
{
	/* Sliding window size (first 3 bits) */
	return h5->tx_win & 0x07;
}