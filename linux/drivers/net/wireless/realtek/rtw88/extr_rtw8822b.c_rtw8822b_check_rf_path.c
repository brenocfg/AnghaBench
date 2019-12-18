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
typedef  int u8 ;

/* Variables and functions */
#define  BB_PATH_A 130 
#define  BB_PATH_AB 129 
#define  BB_PATH_B 128 

__attribute__((used)) static bool rtw8822b_check_rf_path(u8 antenna)
{
	switch (antenna) {
	case BB_PATH_A:
	case BB_PATH_B:
	case BB_PATH_AB:
		return true;
	default:
		return false;
	}
}