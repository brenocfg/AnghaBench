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
struct TYPE_2__ {int /*<<< orphan*/  d0; } ;
struct vring_rx_desc {TYPE_1__ mac; } ;

/* Variables and functions */
 int WIL_GET_BITS (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static inline int wil_rxdesc_ext_subtype(struct vring_rx_desc *d)
{
	return WIL_GET_BITS(d->mac.d0, 28, 31);
}