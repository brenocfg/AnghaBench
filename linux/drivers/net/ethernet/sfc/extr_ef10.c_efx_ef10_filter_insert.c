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
struct efx_nic {int /*<<< orphan*/  filter_sem; } ;
struct efx_filter_spec {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efx_ef10_filter_insert_locked (struct efx_nic*,struct efx_filter_spec*,int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static s32 efx_ef10_filter_insert(struct efx_nic *efx,
				  struct efx_filter_spec *spec,
				  bool replace_equal)
{
	s32 ret;

	down_read(&efx->filter_sem);
	ret = efx_ef10_filter_insert_locked(efx, spec, replace_equal);
	up_read(&efx->filter_sem);

	return ret;
}