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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int fport; int lport; } ;
struct TYPE_3__ {int fport; int lport; } ;
struct ch_filter_specification {TYPE_2__ mask; TYPE_1__ val; } ;

/* Variables and functions */
 int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int cxgb4_fill_l4_ports(struct ch_filter_specification *f,
				      u32 val, u32 mask)
{
	f->val.fport  = ntohl(val)  >> 16;
	f->mask.fport = ntohl(mask) >> 16;
	f->val.lport  = ntohl(val)  & 0x0000FFFF;
	f->mask.lport = ntohl(mask) & 0x0000FFFF;

	return 0;
}