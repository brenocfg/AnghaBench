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
typedef  int /*<<< orphan*/  u32 ;
struct ef4_nic {TYPE_1__* type; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* filter_get_rx_id_limit ) (struct ef4_nic*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ef4_nic*) ; 

__attribute__((used)) static inline u32 ef4_filter_get_rx_id_limit(struct ef4_nic *efx)
{
	return efx->type->filter_get_rx_id_limit(efx);
}