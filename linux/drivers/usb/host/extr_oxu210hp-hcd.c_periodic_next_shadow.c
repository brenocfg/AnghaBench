#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
union ehci_shadow {TYPE_1__* qh; } ;
typedef  int __le32 ;
struct TYPE_2__ {union ehci_shadow qh_next; } ;

/* Variables and functions */
#define  Q_TYPE_QH 128 

__attribute__((used)) static union ehci_shadow *periodic_next_shadow(union ehci_shadow *periodic,
						__le32 tag)
{
	switch (tag) {
	default:
	case Q_TYPE_QH:
		return &periodic->qh->qh_next;
	}
}