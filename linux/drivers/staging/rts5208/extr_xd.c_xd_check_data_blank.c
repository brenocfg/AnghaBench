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
 int PAGE_STATUS ; 
 size_t PARITY ; 
 int RESERVED0 ; 
 int XD_ECC1_ALL1 ; 
 int XD_ECC2_ALL1 ; 

__attribute__((used)) static int xd_check_data_blank(u8 *redunt)
{
	int i;

	for (i = 0; i < 6; i++) {
		if (redunt[PAGE_STATUS + i] != 0xFF)
			return 0;
	}

	if ((redunt[PARITY] & (XD_ECC1_ALL1 | XD_ECC2_ALL1))
		!= (XD_ECC1_ALL1 | XD_ECC2_ALL1))
		return 0;

	for (i = 0; i < 4; i++) {
		if (redunt[RESERVED0 + i] != 0xFF)
			return 0;
	}

	return 1;
}