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
typedef  enum chip_type { ____Placeholder_chip_type } chip_type ;

/* Variables and functions */
 scalar_t__ CHELSIO_CHIP_VERSION (int) ; 
 scalar_t__ CHELSIO_T4 ; 

__attribute__((used)) static inline int is_t4(enum chip_type chip)
{
	return CHELSIO_CHIP_VERSION(chip) == CHELSIO_T4;
}