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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct octeon_hcd {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_USBNX_DMA0_INB_CHN0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_read64_uint64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write64_uint32 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void cvmx_usb_write_csr32(struct octeon_hcd *usb,
					u64 address, u32 value)
{
	cvmx_write64_uint32(address ^ 4, value);
	cvmx_read64_uint64(CVMX_USBNX_DMA0_INB_CHN0(usb->index));
}