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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int kstrtou16 (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  strim (char*) ; 

__attribute__((used)) static int vpdstrtou16(char *s, u8 len, unsigned int base, u16 *val)
{
	char tok[256];

	memcpy(tok, s, len);
	tok[len] = 0;
	return kstrtou16(strim(tok), base, val);
}