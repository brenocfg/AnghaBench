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
typedef  int u32 ;

/* Variables and functions */
 int RHF_RCV_SEQ_MASK ; 
 int RHF_RCV_SEQ_SHIFT ; 

__attribute__((used)) static inline u32 rhf_rcv_seq(u64 rhf)
{
	return (rhf >> RHF_RCV_SEQ_SHIFT) & RHF_RCV_SEQ_MASK;
}