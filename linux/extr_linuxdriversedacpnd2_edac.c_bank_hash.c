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
typedef  int u64 ;

/* Variables and functions */

__attribute__((used)) static int bank_hash(u64 pmiaddr, int idx, int shft)
{
	int bhash = 0;

	switch (idx) {
	case 0:
		bhash ^= ((pmiaddr >> (12 + shft)) ^ (pmiaddr >> (9 + shft))) & 1;
		break;
	case 1:
		bhash ^= (((pmiaddr >> (10 + shft)) ^ (pmiaddr >> (8 + shft))) & 1) << 1;
		bhash ^= ((pmiaddr >> 22) & 1) << 1;
		break;
	case 2:
		bhash ^= (((pmiaddr >> (13 + shft)) ^ (pmiaddr >> (11 + shft))) & 1) << 2;
		break;
	}

	return bhash;
}