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
struct lpfc_vport {TYPE_1__* phba; } ;
struct TYPE_4__ {char* nodename; char* sysname; } ;
struct TYPE_3__ {char* ModelName; } ;

/* Variables and functions */
 int FW_REV_STR_SIZE ; 
 TYPE_2__* init_utsname () ; 
 int /*<<< orphan*/  lpfc_decode_firmware_rev (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 char* lpfc_release_version ; 
 int scnprintf (char*,size_t,char*,char*) ; 

int
lpfc_vport_symbolic_node_name(struct lpfc_vport *vport, char *symbol,
	size_t size)
{
	char fwrev[FW_REV_STR_SIZE];
	int n;

	lpfc_decode_firmware_rev(vport->phba, fwrev, 0);

	n = scnprintf(symbol, size, "Emulex %s", vport->phba->ModelName);
	if (size < n)
		return n;

	n += scnprintf(symbol + n, size - n, " FV%s", fwrev);
	if (size < n)
		return n;

	n += scnprintf(symbol + n, size - n, " DV%s.",
		      lpfc_release_version);
	if (size < n)
		return n;

	n += scnprintf(symbol + n, size - n, " HN:%s.",
		      init_utsname()->nodename);
	if (size < n)
		return n;

	/* Note :- OS name is "Linux" */
	n += scnprintf(symbol + n, size - n, " OS:%s",
		      init_utsname()->sysname);
	return n;
}