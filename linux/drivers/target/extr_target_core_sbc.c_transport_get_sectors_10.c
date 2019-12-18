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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  get_unaligned_be16 (unsigned char*) ; 

__attribute__((used)) static inline u32 transport_get_sectors_10(unsigned char *cdb)
{
	return get_unaligned_be16(&cdb[7]);
}