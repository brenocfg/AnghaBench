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
typedef  int /*<<< orphan*/  PIA ;

/* Variables and functions */
 int /*<<< orphan*/  frpw_read_block_int (int /*<<< orphan*/ *,char*,int,int) ; 

__attribute__((used)) static void frpw_read_block( PIA *pi, char * buf, int count)

{	frpw_read_block_int(pi,buf,count,0x08);
}