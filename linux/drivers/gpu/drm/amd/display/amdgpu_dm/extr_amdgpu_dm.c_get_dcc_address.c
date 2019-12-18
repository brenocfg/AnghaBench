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
typedef  int uint32_t ;

/* Variables and functions */
 int AMDGPU_TILING_GET (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DCC_OFFSET_256B ; 

__attribute__((used)) static inline uint64_t get_dcc_address(uint64_t address, uint64_t tiling_flags)
{
	uint32_t offset = AMDGPU_TILING_GET(tiling_flags, DCC_OFFSET_256B);

	return offset ? (address + offset * 256) : 0;
}