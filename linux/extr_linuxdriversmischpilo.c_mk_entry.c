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
 int ENTRY_BITPOS_DESCRIPTOR ; 
 int ENTRY_BITPOS_QWORDS ; 

__attribute__((used)) static inline int mk_entry(int id, int len)
{
	int qlen = len & 7 ? (len >> 3) + 1 : len >> 3;
	return id << ENTRY_BITPOS_DESCRIPTOR | qlen << ENTRY_BITPOS_QWORDS;
}