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
typedef  unsigned long long u32 ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 unsigned long long SEND_CM_LOCAL_AU_TABLE0_TO3_LOCAL_AU_TABLE0_SHIFT ; 
 unsigned long long SEND_CM_LOCAL_AU_TABLE0_TO3_LOCAL_AU_TABLE1_SHIFT ; 
 unsigned long long SEND_CM_LOCAL_AU_TABLE0_TO3_LOCAL_AU_TABLE2_SHIFT ; 
 unsigned long long SEND_CM_LOCAL_AU_TABLE0_TO3_LOCAL_AU_TABLE3_SHIFT ; 
 unsigned long long SEND_CM_LOCAL_AU_TABLE4_TO7_LOCAL_AU_TABLE4_SHIFT ; 
 unsigned long long SEND_CM_LOCAL_AU_TABLE4_TO7_LOCAL_AU_TABLE5_SHIFT ; 
 unsigned long long SEND_CM_LOCAL_AU_TABLE4_TO7_LOCAL_AU_TABLE6_SHIFT ; 
 unsigned long long SEND_CM_LOCAL_AU_TABLE4_TO7_LOCAL_AU_TABLE7_SHIFT ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,unsigned long long,unsigned long long) ; 

__attribute__((used)) static void assign_cm_au_table(struct hfi1_devdata *dd, u32 cu,
			       u32 csr0to3, u32 csr4to7)
{
	write_csr(dd, csr0to3,
		  0ull << SEND_CM_LOCAL_AU_TABLE0_TO3_LOCAL_AU_TABLE0_SHIFT |
		  1ull << SEND_CM_LOCAL_AU_TABLE0_TO3_LOCAL_AU_TABLE1_SHIFT |
		  2ull * cu <<
		  SEND_CM_LOCAL_AU_TABLE0_TO3_LOCAL_AU_TABLE2_SHIFT |
		  4ull * cu <<
		  SEND_CM_LOCAL_AU_TABLE0_TO3_LOCAL_AU_TABLE3_SHIFT);
	write_csr(dd, csr4to7,
		  8ull * cu <<
		  SEND_CM_LOCAL_AU_TABLE4_TO7_LOCAL_AU_TABLE4_SHIFT |
		  16ull * cu <<
		  SEND_CM_LOCAL_AU_TABLE4_TO7_LOCAL_AU_TABLE5_SHIFT |
		  32ull * cu <<
		  SEND_CM_LOCAL_AU_TABLE4_TO7_LOCAL_AU_TABLE6_SHIFT |
		  64ull * cu <<
		  SEND_CM_LOCAL_AU_TABLE4_TO7_LOCAL_AU_TABLE7_SHIFT);
}