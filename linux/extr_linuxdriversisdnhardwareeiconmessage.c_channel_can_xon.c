#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int word ;
typedef  int dword ;
typedef  size_t byte ;
struct TYPE_7__ {int MaxBuffer; int* DataNCCI; } ;
struct TYPE_6__ {int* ch_ncci; scalar_t__ Id; } ;
struct TYPE_5__ {TYPE_2__* adapter; TYPE_3__* appl; } ;
typedef  TYPE_1__ PLCI ;
typedef  TYPE_2__ DIVA_CAPI_ADAPTER ;
typedef  TYPE_3__ APPL ;

/* Variables and functions */

__attribute__((used)) static int channel_can_xon(PLCI *plci, byte ch) {
	APPL *APPLptr;
	DIVA_CAPI_ADAPTER *a;
	word NCCIcode;
	dword count;
	word Num;
	word i;

	APPLptr = plci->appl;
	a = plci->adapter;

	if (!APPLptr)
		return (0);

	NCCIcode = a->ch_ncci[ch] | (((word) a->Id) << 8);

	/* count all buffers within the Application pool    */
	/* belonging to the same NCCI. XON if a first is    */
	/* used.                                            */
	count = 0;
	Num = 0xffff;
	for (i = 0; i < APPLptr->MaxBuffer; i++) {
		if (NCCIcode == APPLptr->DataNCCI[i]) count++;
		if (!APPLptr->DataNCCI[i] && Num == 0xffff) Num = i;
	}
	if ((count > 2) || (Num == 0xffff)) {
		return (0);
	}
	return (1);
}