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
typedef  int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int*,int,int) ; 

__attribute__((used)) static u8 dlid_to_selector(u16 dlid)
{
	static u8 mapping[256];
	static int initialized;
	static u8 next;
	int hash;

	if (!initialized) {
		memset(mapping, 0xFF, 256);
		initialized = 1;
	}

	hash = ((dlid >> 8) ^ dlid) & 0xFF;
	if (mapping[hash] == 0xFF) {
		mapping[hash] = next;
		next = (next + 1) & 0x7F;
	}

	return mapping[hash];
}