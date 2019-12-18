#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int tcal; int /*<<< orphan*/  sac; int /*<<< orphan*/  format; } ;
struct tccb {TYPE_1__ tcah; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCCB_FORMAT_DEFAULT ; 
 int /*<<< orphan*/  memset (struct tccb*,int /*<<< orphan*/ ,size_t) ; 

void tccb_init(struct tccb *tccb, size_t size, u32 sac)
{
	memset(tccb, 0, size);
	tccb->tcah.format = TCCB_FORMAT_DEFAULT;
	tccb->tcah.sac = sac;
	tccb->tcah.tcal = 12;
}