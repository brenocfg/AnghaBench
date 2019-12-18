#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ksz_desc_info {size_t last; size_t mask; int /*<<< orphan*/  avail; struct ksz_desc* ring; } ;
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
struct TYPE_4__ {TYPE_1__ buf; } ;
struct ksz_desc {TYPE_2__ sw; } ;

/* Variables and functions */
 int /*<<< orphan*/  KS_DESC_RX_MASK ; 

__attribute__((used)) static void get_rx_pkt(struct ksz_desc_info *info, struct ksz_desc **desc)
{
	*desc = &info->ring[info->last];
	info->last++;
	info->last &= info->mask;
	info->avail--;
	(*desc)->sw.buf.data &= ~KS_DESC_RX_MASK;
}