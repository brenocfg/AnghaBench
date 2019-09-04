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
typedef  int /*<<< orphan*/  u32 ;
struct vio_dring_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VDC_TX_RING_SIZE ; 
 int /*<<< orphan*/  vio_dring_avail (struct vio_dring_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 vdc_tx_dring_avail(struct vio_dring_state *dr)
{
	return vio_dring_avail(dr, VDC_TX_RING_SIZE);
}