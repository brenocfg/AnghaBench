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
typedef  size_t word ;
typedef  int byte ;

/* Variables and functions */

__attribute__((used)) static byte ie_compare(byte *ie1, byte *ie2)
{
	word i;
	if (!ie1 || !ie2) return false;
	if (!ie1[0]) return false;
	for (i = 0; i < (word)(ie1[0] + 1); i++) if (ie1[i] != ie2[i]) return false;
	return true;
}