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
typedef  size_t u8 ;

/* Variables and functions */
 int kstrtouint (int /*<<< orphan*/ ,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  strim (char*) ; 

__attribute__((used)) static int vpdstrtouint(char *s, u8 len, unsigned int base, unsigned int *val)
{
	char tok[256];

	memcpy(tok, s, len);
	tok[len] = 0;
	return kstrtouint(strim(tok), base, val);
}