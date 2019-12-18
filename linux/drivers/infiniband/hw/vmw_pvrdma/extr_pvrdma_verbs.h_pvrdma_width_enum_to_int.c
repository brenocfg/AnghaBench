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
typedef  enum pvrdma_port_width { ____Placeholder_pvrdma_port_width } pvrdma_port_width ;

/* Variables and functions */
#define  PVRDMA_WIDTH_12X 131 
#define  PVRDMA_WIDTH_1X 130 
#define  PVRDMA_WIDTH_4X 129 
#define  PVRDMA_WIDTH_8X 128 

__attribute__((used)) static inline int pvrdma_width_enum_to_int(enum pvrdma_port_width width)
{
	switch (width) {
	case PVRDMA_WIDTH_1X:	return  1;
	case PVRDMA_WIDTH_4X:	return  4;
	case PVRDMA_WIDTH_8X:	return  8;
	case PVRDMA_WIDTH_12X:	return 12;
	default:		return -1;
	}
}