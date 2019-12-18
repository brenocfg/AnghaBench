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

/* Variables and functions */
 int get_unaligned_be24 (unsigned char*) ; 

__attribute__((used)) static inline u32 transport_lba_21(unsigned char *cdb)
{
	return get_unaligned_be24(&cdb[1]) & 0x1fffff;
}