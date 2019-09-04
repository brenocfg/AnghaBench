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
#define  ADD_NEW_DISK 144 
#define  BLKROSET 143 
#define  CLUSTERED_DISK_NACK 142 
#define  GET_ARRAY_INFO 141 
#define  GET_BITMAP_FILE 140 
#define  GET_DISK_INFO 139 
#define  HOT_ADD_DISK 138 
#define  HOT_REMOVE_DISK 137 
#define  RAID_AUTORUN 136 
#define  RAID_VERSION 135 
#define  RESTART_ARRAY_RW 134 
#define  RUN_ARRAY 133 
#define  SET_ARRAY_INFO 132 
#define  SET_BITMAP_FILE 131 
#define  SET_DISK_FAULTY 130 
#define  STOP_ARRAY 129 
#define  STOP_ARRAY_RO 128 

__attribute__((used)) static inline bool md_ioctl_valid(unsigned int cmd)
{
	switch (cmd) {
	case ADD_NEW_DISK:
	case BLKROSET:
	case GET_ARRAY_INFO:
	case GET_BITMAP_FILE:
	case GET_DISK_INFO:
	case HOT_ADD_DISK:
	case HOT_REMOVE_DISK:
	case RAID_AUTORUN:
	case RAID_VERSION:
	case RESTART_ARRAY_RW:
	case RUN_ARRAY:
	case SET_ARRAY_INFO:
	case SET_BITMAP_FILE:
	case SET_DISK_FAULTY:
	case STOP_ARRAY:
	case STOP_ARRAY_RO:
	case CLUSTERED_DISK_NACK:
		return true;
	default:
		return false;
	}
}