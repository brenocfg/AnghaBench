#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int goptions; int support1; int support2; int support3; int /*<<< orphan*/  nbchannel; } ;
struct TYPE_4__ {int majorversion; int /*<<< orphan*/  minormanuversion; int /*<<< orphan*/  majormanuversion; scalar_t__ minorversion; } ;
struct TYPE_6__ {int /*<<< orphan*/  serial; TYPE_2__ profile; TYPE_1__ version; int /*<<< orphan*/  manu; } ;
struct gigaset_capi_ctr {TYPE_3__ ctr; } ;
struct cardstate {int /*<<< orphan*/  channels; int /*<<< orphan*/ * fwver; struct gigaset_capi_ctr* iif; } ;

/* Variables and functions */
 int /*<<< orphan*/  capi_ctr_ready (TYPE_3__*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

void gigaset_isdn_start(struct cardstate *cs)
{
	struct gigaset_capi_ctr *iif = cs->iif;

	/* fill profile data: manufacturer name */
	strcpy(iif->ctr.manu, "Siemens");
	/* CAPI and device version */
	iif->ctr.version.majorversion = 2;		/* CAPI 2.0 */
	iif->ctr.version.minorversion = 0;
	/* ToDo: check/assert cs->gotfwver? */
	iif->ctr.version.majormanuversion = cs->fwver[0];
	iif->ctr.version.minormanuversion = cs->fwver[1];
	/* number of B channels supported */
	iif->ctr.profile.nbchannel = cs->channels;
	/* global options: internal controller, supplementary services */
	iif->ctr.profile.goptions = 0x11;
	/* B1 protocols: 64 kbit/s HDLC or transparent */
	iif->ctr.profile.support1 =  0x03;
	/* B2 protocols: transparent only */
	/* ToDo: X.75 SLP ? */
	iif->ctr.profile.support2 =  0x02;
	/* B3 protocols: transparent only */
	iif->ctr.profile.support3 =  0x01;
	/* no serial number */
	strcpy(iif->ctr.serial, "0");
	capi_ctr_ready(&iif->ctr);
}