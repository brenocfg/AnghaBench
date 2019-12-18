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
typedef  int u8 ;
typedef  int u32 ;

/* Variables and functions */
 int NVME_CC_MPS_SHIFT ; 

__attribute__((used)) static inline u8 nvmet_cc_mps(u32 cc)
{
	return (cc >> NVME_CC_MPS_SHIFT) & 0xf;
}