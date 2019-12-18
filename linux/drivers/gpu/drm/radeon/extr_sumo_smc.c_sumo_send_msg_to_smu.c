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
typedef  int u32 ;
struct radeon_device {int usec_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFX_INT_REQ ; 
 int /*<<< orphan*/  GFX_INT_STATUS ; 
 int INT_ACK ; 
 int INT_DONE ; 
 int INT_REQ ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int SERV_INDEX (int) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void sumo_send_msg_to_smu(struct radeon_device *rdev, u32 id)
{
	u32 gfx_int_req;
	int i;

	for (i = 0; i < rdev->usec_timeout; i++) {
		if (RREG32(GFX_INT_STATUS) & INT_DONE)
			break;
		udelay(1);
	}

	gfx_int_req = SERV_INDEX(id) | INT_REQ;
	WREG32(GFX_INT_REQ, gfx_int_req);

	for (i = 0; i < rdev->usec_timeout; i++) {
		if (RREG32(GFX_INT_REQ) & INT_REQ)
			break;
		udelay(1);
	}

	for (i = 0; i < rdev->usec_timeout; i++) {
		if (RREG32(GFX_INT_STATUS) & INT_ACK)
			break;
		udelay(1);
	}

	for (i = 0; i < rdev->usec_timeout; i++) {
		if (RREG32(GFX_INT_STATUS) & INT_DONE)
			break;
		udelay(1);
	}

	gfx_int_req &= ~INT_REQ;
	WREG32(GFX_INT_REQ, gfx_int_req);
}