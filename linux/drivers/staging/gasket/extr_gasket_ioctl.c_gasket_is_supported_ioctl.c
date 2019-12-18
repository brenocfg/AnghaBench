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
typedef  int uint ;

/* Variables and functions */
#define  GASKET_IOCTL_CLEAR_EVENTFD 138 
#define  GASKET_IOCTL_CLEAR_INTERRUPT_COUNTS 137 
#define  GASKET_IOCTL_CONFIG_COHERENT_ALLOCATOR 136 
#define  GASKET_IOCTL_MAP_BUFFER 135 
#define  GASKET_IOCTL_NUMBER_PAGE_TABLES 134 
#define  GASKET_IOCTL_PAGE_TABLE_SIZE 133 
#define  GASKET_IOCTL_PARTITION_PAGE_TABLE 132 
#define  GASKET_IOCTL_RESET 131 
#define  GASKET_IOCTL_SET_EVENTFD 130 
#define  GASKET_IOCTL_SIMPLE_PAGE_TABLE_SIZE 129 
#define  GASKET_IOCTL_UNMAP_BUFFER 128 

long gasket_is_supported_ioctl(uint cmd)
{
	switch (cmd) {
	case GASKET_IOCTL_RESET:
	case GASKET_IOCTL_SET_EVENTFD:
	case GASKET_IOCTL_CLEAR_EVENTFD:
	case GASKET_IOCTL_PARTITION_PAGE_TABLE:
	case GASKET_IOCTL_NUMBER_PAGE_TABLES:
	case GASKET_IOCTL_PAGE_TABLE_SIZE:
	case GASKET_IOCTL_SIMPLE_PAGE_TABLE_SIZE:
	case GASKET_IOCTL_MAP_BUFFER:
	case GASKET_IOCTL_UNMAP_BUFFER:
	case GASKET_IOCTL_CLEAR_INTERRUPT_COUNTS:
	case GASKET_IOCTL_CONFIG_COHERENT_ALLOCATOR:
		return 1;
	default:
		return 0;
	}
}