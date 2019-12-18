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
 int QOS_AC_BE ; 
 int QOS_AC_BK ; 
 int QOS_AC_VI ; 
 int QOS_AC_VO ; 

__attribute__((used)) static inline int wl1251_tx_get_queue(int queue)
{
	switch (queue) {
	case 0:
		return QOS_AC_VO;
	case 1:
		return QOS_AC_VI;
	case 2:
		return QOS_AC_BE;
	case 3:
		return QOS_AC_BK;
	default:
		return QOS_AC_BE;
	}
}