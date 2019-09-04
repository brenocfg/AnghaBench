#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ start; scalar_t__ ptr; scalar_t__ end; } ;
struct TYPE_3__ {TYPE_2__ buf; } ;
struct lanai_vcc {TYPE_1__ rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  memcpy (unsigned char*,scalar_t__,int) ; 

__attribute__((used)) static inline void vcc_rx_memcpy(unsigned char *dest,
	const struct lanai_vcc *lvcc, int n)
{
	int m = ((const unsigned char *) lvcc->rx.buf.ptr) + n -
	    ((const unsigned char *) (lvcc->rx.buf.end));
	if (m < 0)
		m = 0;
	memcpy(dest, lvcc->rx.buf.ptr, n - m);
	memcpy(dest + n - m, lvcc->rx.buf.start, m);
	/* Make sure that these copies don't get reordered */
	barrier();
}