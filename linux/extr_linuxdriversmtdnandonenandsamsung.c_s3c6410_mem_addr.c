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

/* Variables and functions */
 int S3C6410_FBA_SHIFT ; 
 int S3C6410_FPA_SHIFT ; 
 int S3C6410_FSA_SHIFT ; 

__attribute__((used)) static unsigned int s3c6410_mem_addr(int fba, int fpa, int fsa)
{
	return (fba << S3C6410_FBA_SHIFT) | (fpa << S3C6410_FPA_SHIFT) |
		(fsa << S3C6410_FSA_SHIFT);
}