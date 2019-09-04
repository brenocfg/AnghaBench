#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int goptions; int support1; int support2; int support3; int /*<<< orphan*/  nbchannel; int /*<<< orphan*/  ncontroller; } ;
struct TYPE_6__ {int majorversion; int majormanuversion; int minormanuversion; scalar_t__ minorversion; } ;
struct capi_ctr {TYPE_2__ profile; TYPE_1__ version; int /*<<< orphan*/  manu; } ;
struct TYPE_8__ {scalar_t__ faxchans; int /*<<< orphan*/  bchans; int /*<<< orphan*/  myid; TYPE_4__* hyctrlinfo; } ;
typedef  TYPE_3__ hysdn_card ;
struct TYPE_9__ {struct capi_ctr capi_ctrl; } ;
typedef  TYPE_4__ hycapictrl_info ;

/* Variables and functions */
 int B1_PROT_64KBIT_HDLC ; 
 int B1_PROT_64KBIT_TRANSPARENT ; 
 int B1_PROT_T30 ; 
 int B2_PROT_ISO7776 ; 
 int B2_PROT_T30 ; 
 int B2_PROT_TRANSPARENT ; 
 int B3_PROT_ISO8208 ; 
 int B3_PROT_T30 ; 
 int B3_PROT_T30EXT ; 
 int B3_PROT_T90NL ; 
 int B3_PROT_TRANSPARENT ; 
 int GLOBAL_OPTION_B_CHANNEL_OPERATION ; 
 int GLOBAL_OPTION_INTERNAL_CONTROLLER ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void hycapi_fill_profile(hysdn_card *card)
{
	hycapictrl_info *cinfo = NULL;
	struct capi_ctr *ctrl = NULL;
	cinfo = card->hyctrlinfo;
	if (!cinfo) return;
	ctrl = &cinfo->capi_ctrl;
	strcpy(ctrl->manu, "Hypercope");
	ctrl->version.majorversion = 2;
	ctrl->version.minorversion = 0;
	ctrl->version.majormanuversion = 3;
	ctrl->version.minormanuversion = 2;
	ctrl->profile.ncontroller = card->myid;
	ctrl->profile.nbchannel = card->bchans;
	ctrl->profile.goptions = GLOBAL_OPTION_INTERNAL_CONTROLLER |
		GLOBAL_OPTION_B_CHANNEL_OPERATION;
	ctrl->profile.support1 =  B1_PROT_64KBIT_HDLC |
		(card->faxchans ? B1_PROT_T30 : 0) |
		B1_PROT_64KBIT_TRANSPARENT;
	ctrl->profile.support2 = B2_PROT_ISO7776 |
		(card->faxchans ? B2_PROT_T30 : 0) |
		B2_PROT_TRANSPARENT;
	ctrl->profile.support3 = B3_PROT_TRANSPARENT |
		B3_PROT_T90NL |
		(card->faxchans ? B3_PROT_T30 : 0) |
		(card->faxchans ? B3_PROT_T30EXT : 0) |
		B3_PROT_ISO8208;
}