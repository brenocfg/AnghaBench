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
struct vivid_rds_gen {int picode; int pty; int mono_stereo; int art_head; int compressed; int dyn_pty; int tp; int ta; int ms; int /*<<< orphan*/  radiotext; int /*<<< orphan*/  psname; scalar_t__ use_rbds; } ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 

void vivid_rds_gen_fill(struct vivid_rds_gen *rds, unsigned freq,
			  bool alt)
{
	/* Alternate PTY between Info and Weather */
	if (rds->use_rbds) {
		rds->picode = 0x2e75; /* 'KLNX' call sign */
		rds->pty = alt ? 29 : 2;
	} else {
		rds->picode = 0x8088;
		rds->pty = alt ? 16 : 3;
	}
	rds->mono_stereo = true;
	rds->art_head = false;
	rds->compressed = false;
	rds->dyn_pty = false;
	rds->tp = true;
	rds->ta = alt;
	rds->ms = true;
	snprintf(rds->psname, sizeof(rds->psname), "%6d.%1d",
		 freq / 16, ((freq & 0xf) * 10) / 16);
	if (alt)
		strscpy(rds->radiotext,
			" The Radio Data System can switch between different Radio Texts ",
			sizeof(rds->radiotext));
	else
		strscpy(rds->radiotext,
			"An example of Radio Text as transmitted by the Radio Data System",
			sizeof(rds->radiotext));
}