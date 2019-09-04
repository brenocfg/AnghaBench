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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct dac_audio_pdata {int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  HD64461_GPADR ; 
 int /*<<< orphan*/  HD64461_GPADR_SPEAKER ; 
 int /*<<< orphan*/  PKDR ; 
 int /*<<< orphan*/  PKDR_SPEAKER ; 
 int /*<<< orphan*/  inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_dac_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dac_audio_start(struct dac_audio_pdata *pdata)
{
	u16 v;
	u8 v8;

	/* HP Jornada 680/690 speaker on */
	v = inw(HD64461_GPADR);
	v &= ~HD64461_GPADR_SPEAKER;
	outw(v, HD64461_GPADR);

	/* HP Palmtop 620lx/660lx speaker on */
	v8 = inb(PKDR);
	v8 &= ~PKDR_SPEAKER;
	outb(v8, PKDR);

	sh_dac_enable(pdata->channel);
}