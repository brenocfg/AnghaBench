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
 int SJA1105ET_FDB_BIN_SIZE ; 

__attribute__((used)) static inline int sja1105et_fdb_index(int bin, int way)
{
	return bin * SJA1105ET_FDB_BIN_SIZE + way;
}