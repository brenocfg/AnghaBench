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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  put_unaligned_be64 (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int,int,int,int,int,int,int,int) ; 

ssize_t ft_format_wwn(char *buf, size_t len, u64 wwn)
{
	u8 b[8];

	put_unaligned_be64(wwn, b);
	return snprintf(buf, len,
		 "%2.2x:%2.2x:%2.2x:%2.2x:%2.2x:%2.2x:%2.2x:%2.2x",
		 b[0], b[1], b[2], b[3], b[4], b[5], b[6], b[7]);
}