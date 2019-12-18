#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* type; } ;
struct TYPE_7__ {TYPE_4__ scsi; } ;
struct cumanascsi2_info {scalar_t__ terms; TYPE_1__* ec; TYPE_3__ info; } ;
struct Scsi_Host {TYPE_2__* hostt; scalar_t__ hostdata; } ;
struct TYPE_6__ {char* name; } ;
struct TYPE_5__ {int slot_no; } ;

/* Variables and functions */
 char* VERSION ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*,int,char*,char*) ; 

const char *cumanascsi_2_info(struct Scsi_Host *host)
{
	struct cumanascsi2_info *info = (struct cumanascsi2_info *)host->hostdata;
	static char string[150];

	sprintf(string, "%s (%s) in slot %d v%s terminators o%s",
		host->hostt->name, info->info.scsi.type, info->ec->slot_no,
		VERSION, info->terms ? "n" : "ff");

	return string;
}