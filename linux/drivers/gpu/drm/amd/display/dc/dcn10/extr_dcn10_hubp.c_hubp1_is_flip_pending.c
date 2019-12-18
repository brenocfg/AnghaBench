#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_6__ {scalar_t__ quad_part; } ;
struct TYPE_7__ {TYPE_1__ addr; } ;
struct TYPE_8__ {TYPE_2__ grph; } ;
struct hubp {TYPE_3__ request_address; } ;
struct dcn10_hubp {int dummy; } ;
struct TYPE_9__ {scalar_t__ quad_part; scalar_t__ high_part; scalar_t__ low_part; } ;
struct TYPE_10__ {TYPE_4__ addr; } ;
struct dc_plane_address {TYPE_5__ grph; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCSURF_FLIP_CONTROL ; 
 int /*<<< orphan*/  DCSURF_SURFACE_EARLIEST_INUSE ; 
 int /*<<< orphan*/  DCSURF_SURFACE_EARLIEST_INUSE_HIGH ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  SURFACE_EARLIEST_INUSE_ADDRESS ; 
 int /*<<< orphan*/  SURFACE_EARLIEST_INUSE_ADDRESS_HIGH ; 
 int /*<<< orphan*/  SURFACE_FLIP_PENDING ; 
 struct dcn10_hubp* TO_DCN10_HUBP (struct hubp*) ; 

bool hubp1_is_flip_pending(struct hubp *hubp)
{
	uint32_t flip_pending = 0;
	struct dcn10_hubp *hubp1 = TO_DCN10_HUBP(hubp);
	struct dc_plane_address earliest_inuse_address;

	REG_GET(DCSURF_FLIP_CONTROL,
			SURFACE_FLIP_PENDING, &flip_pending);

	REG_GET(DCSURF_SURFACE_EARLIEST_INUSE,
			SURFACE_EARLIEST_INUSE_ADDRESS, &earliest_inuse_address.grph.addr.low_part);

	REG_GET(DCSURF_SURFACE_EARLIEST_INUSE_HIGH,
			SURFACE_EARLIEST_INUSE_ADDRESS_HIGH, &earliest_inuse_address.grph.addr.high_part);

	if (flip_pending)
		return true;

	if (earliest_inuse_address.grph.addr.quad_part != hubp->request_address.grph.addr.quad_part)
		return true;

	return false;
}