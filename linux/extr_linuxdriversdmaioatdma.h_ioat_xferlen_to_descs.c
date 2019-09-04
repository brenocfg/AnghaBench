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
typedef  int u16 ;
struct ioatdma_chan {size_t xfercap_log; } ;

/* Variables and functions */

__attribute__((used)) static inline u16
ioat_xferlen_to_descs(struct ioatdma_chan *ioat_chan, size_t len)
{
	u16 num_descs = len >> ioat_chan->xfercap_log;

	num_descs += !!(len & ((1 << ioat_chan->xfercap_log) - 1));
	return num_descs;
}