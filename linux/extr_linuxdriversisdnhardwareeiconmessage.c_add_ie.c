#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int word ;
typedef  int byte ;
struct TYPE_3__ {scalar_t__ req_in; scalar_t__ req_in_start; int* RBuffer; } ;
typedef  TYPE_1__ PLCI ;

/* Variables and functions */

__attribute__((used)) static void add_ie(PLCI *plci, byte code, byte *p, word p_length)
{
	word i;

	if (!(code & 0x80) && !p_length) return;

	if (plci->req_in == plci->req_in_start) {
		plci->req_in += 2;
	}
	else {
		plci->req_in--;
	}
	plci->RBuffer[plci->req_in++] = code;

	if (p) {
		plci->RBuffer[plci->req_in++] = (byte)p_length;
		for (i = 0; i < p_length; i++) plci->RBuffer[plci->req_in++] = p[1 + i];
	}

	plci->RBuffer[plci->req_in++] = 0;
}