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
typedef  scalar_t__ uint64_t ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ RREG32_PCIE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixPCIE_RX_NUM_NAK ; 
 int /*<<< orphan*/  ixPCIE_RX_NUM_NAK_GENERATED ; 

__attribute__((used)) static uint64_t cik_get_pcie_replay_count(struct amdgpu_device *adev)
{
	uint64_t nak_r, nak_g;

	/* Get the number of NAKs received and generated */
	nak_r = RREG32_PCIE(ixPCIE_RX_NUM_NAK);
	nak_g = RREG32_PCIE(ixPCIE_RX_NUM_NAK_GENERATED);

	/* Add the total number of NAKs, i.e the number of replays */
	return (nak_r + nak_g);
}