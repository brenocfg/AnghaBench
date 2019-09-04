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
 int /*<<< orphan*/  op (int) ; 
 int /*<<< orphan*/  vl (int) ; 
 int /*<<< orphan*/  w0 (char) ; 
 int /*<<< orphan*/  w2 (int) ; 

__attribute__((used)) static void on20_write_block(  PIA *pi, char * buf, int count )

{	int	k;

	op(1); vl(1); op(0);

	for (k=0;k<count;k++) { w2(5); w0(buf[k]); w2(7); }
	w2(4);
}